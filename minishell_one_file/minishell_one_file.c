/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_one_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:21:52 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/07 10:31:40 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <fcntl.h>

#define ERROR_MINISHELL "Error : exit minishell\n"
#define WARNING "NOT INLINE MODE\n!!!!!!"
#define SYNTAX_ERROR "\nminishell: syntax error: unexpected end of file\n"
#define SIZE_OF_ONE_CHAR_STR 2
#define SIZE_OF_TWO_CHAR_STR 3
#define ERROR_OPERATOR "\nminishell: the `&' operator is not handled by minishell\n"
#define SYNTAX_ERROR_LEX "\nminishell: syntax error\n"

/*"
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<< LEXER >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/

/*
 * All the possible char types. during the lexing phase the proper tokenizer
 * will be called accordingly to the type encountered
*/

enum e_char_type
{
	ANY_CHAR,
	NULL_CHAR,
	SPACE_CHAR,
	SQUOTE_CHAR,
	DQUOTES_CHAR,
	LESS_CHAR,
	GREAT_CHAR,
	AND_CHAR,
	SEMICO_CHAR,
	PIPE_CHAR,
	OP_PARENTH_CHAR,
	CLOSE_PARENTH_CHAR,
	NB_CHAR_TYPE
};

/*
 * All type of tokens handled by program
*/

enum e_token_type
{
	WORD_TOKEN,
	PIPE_TOKEN,
	OR_TOKEN,
	AND_TOKEN,
	SEMICO_TOKEN,
	LESSER_TOKEN,
	DOUBLE_LESSER_TOKEN,
	GREATER_TOKEN,
	DOUBLE_GREATER_TOKEN,
	AMPERSAND_TOKEN,
	OP_PARENTH_TOKEN,
	CLOSE_PARENTH_TOKEN
};

/*
 * Word rules
*/

enum e_char_rules
{
	NOT_ACCEPTED,
	ACCEPTED,
};

/*
 * TOKEN LINKED LIST
*/

typedef struct s_token
{
	char				*data;
	enum e_token_type	type;
	struct s_token		*next;
}	t_token;

/*
 * <<<<<<<<<<<<<<<<<<<<<<<>><<<< PARSER >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/

/*
 * All code types of nodes that can be found in out AST,
 * leaves are considered as nodes
*/

enum e_node_type
{
	SIMPLE_CMD,
	PIPE_NODE,
	OR_NODE,
	AND_NODE,
	SEMICO_NODE
};

/*
 * All the possible types of redirections that can be found in a cmd
*/

enum e_redirection_type
{
	INPUT_REDIR,
	HEREDOC_REDIR,
	OUTPUT_REDIR,
	APPEND_OUTPUT_REDIR,
	NO_REDIR
};

/*
 * Simple cmd
*/

typedef struct s_simple_cmd
{
	char	**argv;
	int		fd_in;
	int		fd_out;
	bool	input_stream_has_quotes;
}	t_simple_cmd;

/*
 * A node in our AST always has children, one on the left, and one one
 * the right
*/

typedef struct s_child
{
	struct s_node	*left;
	struct s_node	*right;
}	t_child;

/*
 * If the member of the AST is a leaf, it contains a simple command,
 * otherwise if it is a node, is had two childs !
*/

typedef union u_node_content
{
	struct s_simple_cmd	simple_cmd;
	struct s_child		child;
}	t_node_content;

/*
 * A member of the AST contains a node_type and a content which can be a
 * simple command or a child
*/

typedef	struct s_node
{
	enum e_node_type	type;
	t_node_content		content;
}	t_node;

/*****************************************************************************/

typedef struct s_garbage_lst
{
	void					*ptr;
	struct s_garbage_lst	*next;
}							t_garbage_lst;

/*****************************************************************************/

bool	build_abstract_syntax_tree(t_token **tok_lst, t_node **ast, bool is_subshell);

/*
 * Function to print content of env
*/

void	ft_print_envp(char **env)
{
	int	param;

	param = 0x0;
	while (env[param])
	{
		printf("%s\n", env[param]);
		param++;
	}
}

/*
 * read input from stdin and return a line
*/

char	*read_line(bool inline_mode)
{
	char	*line;

	line = NULL;
	if (inline_mode == false)
	{
		line = readline("minishell$>");
		if (line != NULL && line[0] == EOF)
		{
			printf("Annie ar you ok ? Are you ok annie ?");
			exit(EXIT_FAILURE);
		}
		//add_history(line);
	}
	else
		write(2, WARNING, sizeof(WARNING));
	return (line);
}

/*skip white spaces*/

int	ft_skip_white_spaces(int c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

/*
** Returns the char type chr_type of char c, in order to call the proper
** tokenizer during the lexing phase.
*/

enum e_char_type get_char_type(char c)
{
	enum e_char_type const	char_type[128] = {
		AND_CHAR,
		['\t' ...'\r'] = SPACE_CHAR,
		[' '] = SPACE_CHAR,
		['\"'] = DQUOTES_CHAR,
		['&'] = AND_CHAR,
		['\''] = SQUOTE_CHAR,
		['('] = OP_PARENTH_CHAR,
		[')'] = CLOSE_PARENTH_CHAR,
		[';'] = SEMICO_CHAR,
		['<'] = LESS_CHAR,
		['>'] = GREAT_CHAR,
		['|'] = PIPE_CHAR
	};

	if (c == '\0')
		return (NULL_CHAR);
	return (char_type[(int)c]);
}

/*
** List the rules of acceptance of a character in a word token without taking in
** account the presence of quotes (which will be verified by the is_valid()
** function.
*/

enum e_char_rules	word_rules(enum e_char_type char_type)
{
	enum e_char_rules const	word_rules[] = {
		[NULL_CHAR] = NOT_ACCEPTED,
		[AND_CHAR] = ACCEPTED,
		[SPACE_CHAR] = NOT_ACCEPTED,
		[SQUOTE_CHAR] = ACCEPTED,
		[DQUOTES_CHAR] = ACCEPTED,
		[LESS_CHAR] = NOT_ACCEPTED,
		[GREAT_CHAR] = NOT_ACCEPTED,
		[SEMICO_CHAR] = NOT_ACCEPTED,
		[PIPE_CHAR] = NOT_ACCEPTED,
		[OP_PARENTH_CHAR] = NOT_ACCEPTED,
		[CLOSE_PARENTH_CHAR] = NOT_ACCEPTED
	};

	return (word_rules[char_type]);
}

/*
** Check for the validity of the characters in scanned_line with the word_rules()
** function according to the quoting state (between two single quotes or two
** double quotes, all the characters are accepted). If the end of the scanned_line
** string is reached and one of the quote state is still equal to true, error is
** set to Unexpected_eof and false is returned. Otherwise, true is returned.
*/

enum e_char_rules	is_valid(
	char c, bool *is_in_squotes, bool *is_in_dquotes)
{
	enum e_char_type	char_type;

	char_type = get_char_type(c);
	if (*is_in_squotes == false && *is_in_dquotes == false)
	{
		if (char_type == SQUOTE_CHAR)
			*is_in_squotes = true;
		else if (char_type == DQUOTES_CHAR)
			*is_in_dquotes = true;
	}
	else
	{
		if (char_type == NULL_CHAR)
			return (NOT_ACCEPTED);
		if (char_type == SQUOTE_CHAR && *is_in_squotes == true)
			*is_in_squotes = false;
		else if (char_type == DQUOTES_CHAR && *is_in_dquotes == true)
			*is_in_dquotes = false;
		return (ACCEPTED);
	}
	return (word_rules(char_type));
}
void	garbage_memdel(void **ap)
{
	if (ap && *ap)
	{
		free(*ap);
		*ap = NULL;
	}
}

t_garbage_lst	**get_garbage_lst(void)
{
	static t_garbage_lst	*garbage_lst = NULL;

	return (&garbage_lst);
}

size_t	ft_strnlen(char const *s, size_t maxlen)
{
	size_t		size;

	size = 0;
	if (!s)
		return (0);
	while (*(s + size) && maxlen--)
		size++;
	return (size);
}

void	*ft_memcpy(void *dst, void const *src, size_t n)
{
	unsigned char		*tmp;

	if (!dst && !src)
		return (NULL);
	tmp = dst;
	while (n--)
		*tmp++ = *(unsigned char *)src++;
	return (dst);
}

void	garbage_putstr_fd(int fd, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

void	garbage_exit(int status, char *message)
{
	if (message != NULL)
	{
		if (status == EXIT_FAILURE)
			garbage_putstr_fd(STDERR_FILENO, "Error: ");
		garbage_putstr_fd(STDERR_FILENO, message);
		garbage_putstr_fd(STDERR_FILENO, "\n");
	}
	exit(status);
}

void	garbage_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

void	*garbage_malloc(size_t size)
{
	t_garbage_lst	*tmp;
	t_garbage_lst	*new;
	t_garbage_lst	**garbage_lst;

	new = NULL;
	garbage_lst = get_garbage_lst();
	tmp = *garbage_lst;
	new = malloc(sizeof(t_garbage_lst) * 1);
	if (new == NULL)
		garbage_exit(EXIT_FAILURE, "malloc(): failed to allocate memory.\n");
	garbage_bzero(new, sizeof(t_garbage_lst) * 1);
	new->ptr = malloc(size);
	if (new->ptr == NULL)
	{
		garbage_memdel((void **)&new);
		garbage_exit(EXIT_FAILURE, "malloc(): failed to allocate memory.\n");
	}
	garbage_bzero(new->ptr, size);
	new->next = tmp;
	*garbage_lst = new;
	return (new->ptr);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;
	size_t	maxlen;

	if (!s1)
		return (NULL);
	maxlen = ft_strnlen(s1, n);
	str = NULL;
	str = garbage_malloc(sizeof(*str) * (maxlen + 1));
	*(str + maxlen) = '\0';
	return (ft_memcpy(str, s1, maxlen));
}

/*
** Create a token link of type type with the malloced data data.
*/

t_token	*create_token(char *data, enum e_token_type type)
{
	t_token	*new_tok;

	new_tok = garbage_malloc(sizeof(*new_tok));
	new_tok->data = data;
	new_tok->type = type;
	new_tok->next = NULL;
	return (new_tok);
}

void	garbage_free(void **garbage_to_free)
{
	t_garbage_lst	**garbage_lst;
	t_garbage_lst	*current;
	t_garbage_lst	*previous;

	previous = NULL;
	if (*garbage_to_free != NULL && garbage_to_free != NULL)
	{
		garbage_lst = get_garbage_lst();
		current = *garbage_lst;
		while (current->ptr != *garbage_to_free)
		{
			previous = current;
			current = current->next;
		}
		if (previous == NULL)
			*garbage_lst = current->next;
		else
			previous->next = current->next;
		garbage_memdel((void **)&current->ptr);
		garbage_memdel((void **)&current);
		*garbage_to_free = NULL;
	}
}

/*
** Starting from the beginning of the token in the scanned_line string, the validity
** of the characters is checked by the is_valid() function. If the character is
** not valid, the end of the token is reached and ft_strndup() function will add the word
** identifier to the data field of the token link.
** The states is_in_squotes and is_in_dquotes are declared here but are modified
** in is_valid() because these states must be persistent from one call to
** is_valid() to another.
*/

t_token	*tokenize_word(char *scanned_line, int *i)
{
	char	*data;
	int		j;
	bool	is_in_squotes;
	bool	is_in_dquotes;

	j = 0x0;
	is_in_squotes = false;
	is_in_dquotes = false;
	data = garbage_malloc(sizeof(*data) * 1);
	*data = '\0';
	while (is_valid(scanned_line[*i + j], &is_in_squotes, &is_in_dquotes)
		== ACCEPTED)
		++j;
	if (scanned_line[*i + j] == '\0'\
		&& (is_in_squotes == true || is_in_dquotes == true))
	{
		write(2, SYNTAX_ERROR, sizeof(SYNTAX_ERROR));
		garbage_free((void **)&data);
		return (NULL);
	}
	data = ft_strndup(scanned_line + *i, j);
	*i += j;
	return (create_token(data, WORD_TOKEN));
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, char const *src, size_t dstsize)
{
	size_t		len_src;

	len_src = ft_strlen(src);
	if (dstsize > len_src)
		ft_memcpy(dst, src, len_src + 1);
	else if (dstsize)
	{
		ft_memcpy(dst, src, dstsize - 1);
		*(dst + dstsize - 1) = '\0';
	}
	return (len_src);
}

/*
** Tokenize the Lesser_tok and the Dlesser_tok tokens.
*/

t_token	*tokenize_lesser(char *scanned_line, int *i)
{
	char			*data;
	enum e_token_type	type;

	if (get_char_type(scanned_line[++(*i)]) == LESS_CHAR)
	{
		data = garbage_malloc(sizeof(*data) * SIZE_OF_TWO_CHAR_STR);
		ft_strlcpy(data, "<<", SIZE_OF_TWO_CHAR_STR);
		type = DOUBLE_LESSER_TOKEN;
		++(*i);
	}
	else
	{
		data = garbage_malloc(sizeof(*data) * SIZE_OF_ONE_CHAR_STR);
		ft_strlcpy(data, "<", SIZE_OF_ONE_CHAR_STR);
		type = LESSER_TOKEN;
	}
	return (create_token(data, type));
}

/*
** Tokenize the Greater_tok and the Dgreater_tok tokens.
*/

t_token	*tokenize_greater(char *scanned_line, int *i)
{
	char			*data;
	enum e_token_type	type;

	if (get_char_type(scanned_line[++(*i)]) == GREAT_CHAR)
	{
		data = garbage_malloc(sizeof(*data) * SIZE_OF_TWO_CHAR_STR);
		ft_strlcpy(data, ">>", SIZE_OF_TWO_CHAR_STR);
		type = DOUBLE_GREATER_TOKEN;
		++(*i);
	}
	else
	{
		data = garbage_malloc(sizeof(*data) * SIZE_OF_ONE_CHAR_STR);
		ft_strlcpy(data, ">", SIZE_OF_ONE_CHAR_STR);
		type = GREATER_TOKEN;
	}
	return (create_token(data, type));
}

/*
** Tokenize the And_tok and the Amp_tok tokens. Since the Amp_tok token is not
** handled by minishell, if this token is found, NULL is returned and an error
** message is displayed.
*/

t_token	*tokenize_and(char *scanned_line, int *i)
{
	enum e_token_type	type;
	char				*data;

	if (get_char_type(scanned_line[++(*i)]) == AND_CHAR)
	{
		data = garbage_malloc(sizeof(*data) * SIZE_OF_TWO_CHAR_STR);
		ft_strlcpy(data, "&&", SIZE_OF_TWO_CHAR_STR);
		type = AND_TOKEN;
		++(*i);
	}
	else
	{
		write(2, ERROR_OPERATOR,sizeof(ERROR_OPERATOR));
		return (NULL);
	}
	return (create_token(data, type));
}

/*
** Tokenize the Semic_tok tokens.
*/

t_token	*tokenize_semic(char *scanned_line, int *i)
{
	char	*data;

	(void)scanned_line;
	data = garbage_malloc(sizeof(*data) * SIZE_OF_ONE_CHAR_STR);
	ft_strlcpy(data, ";", SIZE_OF_ONE_CHAR_STR);
	++(*i);
	return (create_token(data, SEMICO_TOKEN));
}

/*
** Tokenize the Pipe_tok and the Or_tok tokens.
*/

t_token	*tokenize_pipe(char *scanned_line, int *i)
{
	enum e_token_type	type;
	char			*data;

	if (get_char_type(scanned_line[++(*i)]) == PIPE_CHAR)
	{
		data = garbage_malloc(sizeof(*data) * SIZE_OF_TWO_CHAR_STR);
		ft_strlcpy(data, "||", SIZE_OF_TWO_CHAR_STR);
		type = OR_TOKEN;
		++(*i);
	}
	else
	{
		data = garbage_malloc(sizeof(*data) * SIZE_OF_ONE_CHAR_STR);
		ft_strlcpy(data, "|", SIZE_OF_ONE_CHAR_STR);
		type = PIPE_TOKEN;
	}
	return (create_token(data, type));
}


/*
** Tokenize the Oparenth_tok and the Cparenth_tok tokens.
*/

t_token	*tokenize_parenth(char *scanned_line, int *i)
{
	char			*data;
	enum e_token_type	type;

	if (scanned_line[*i] == '(')
		type = OP_PARENTH_TOKEN;
	else
		type = CLOSE_PARENTH_TOKEN;
	data = garbage_malloc(sizeof(*data) * SIZE_OF_ONE_CHAR_STR);
	ft_strlcpy(data, &scanned_line[*i], SIZE_OF_ONE_CHAR_STR);
	++(*i);
	return (create_token(data, type));
}


/*
** The retrieve_next_token() function call from a function pointer array the proper
** tokenizer depending on the type of the char encountered in the scanned_line string
*/

t_token	*retrieve_next_token(char	*scanned_line, int *i)
{
	t_token	*(*tokenizer[NB_CHAR_TYPE])(char*, int*);

	tokenizer[NULL_CHAR] = NULL;
	tokenizer[ANY_CHAR] = &tokenize_word;
	tokenizer[SPACE_CHAR] = NULL;
	tokenizer[SQUOTE_CHAR] = &tokenize_word;
	tokenizer[DQUOTES_CHAR] = &tokenize_word;
	tokenizer[LESS_CHAR] = &tokenize_lesser;
	tokenizer[GREAT_CHAR] = &tokenize_greater;
	tokenizer[AND_CHAR] = &tokenize_and;
	tokenizer[SEMICO_CHAR] = &tokenize_semic;
	tokenizer[PIPE_CHAR] = &tokenize_pipe;
	tokenizer[OP_PARENTH_CHAR] = &tokenize_parenth;
	tokenizer[CLOSE_PARENTH_CHAR] = &tokenize_parenth;
	return (tokenizer[get_char_type(scanned_line[*i])](scanned_line, i));
}

/*
** Add the new_tok token to the tok_lst token linked list.
*/

void	add_token(t_token *new_tok, t_token **tok_lst)
{
	t_token	*current;

	if (*tok_lst == NULL)
		*tok_lst = new_tok;
	else
	{
		current = *tok_lst;
		while (current->next)
			current = current->next;
		current->next = new_tok;
	}
}


/*
 *	Build the tokens linked chained linked list, from the scanned line,
 *	all the white spaces are skipped, the lexer returns true on success,
 *	false otherwise
*/

bool	lexer(char *scanned_line, t_token **token_list)
{
	int		i;
	t_token	*new_token;

	i = 0;
	while (ft_skip_white_spaces(scanned_line[i]))
		++i;
	//printf("%s\n", scanned_line);
	if (scanned_line[i])
	{
		//printf("INFINITE LOOP ??????\n");
		new_token = retrieve_next_token(scanned_line, &i);
		if (new_token == NULL)
			return (false);
		add_token(new_token, token_list);
		while (ft_skip_white_spaces(scanned_line[i]))
			++i;
		//printf("%s\n", scanned_line);
		//printf("INFINITE LOOP ==> Change WHILE to IF\n");
	}
	return (true);
}

/*
** Returns true if the token is '&&', '||' or ';'. Otherwise, returns false.
*/

bool	is_logical_operator(enum e_token_type type)
{
	return (type == SEMICO_TOKEN || type == OR_TOKEN || type == AND_TOKEN);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

/*
** This function is used by all the parsers during the building of the AST: it
** "devour" the next token, meaning freeing the first token of the tok_lst token
** list (using gc_free from the libgc) and setting the head of tok_lst to the
** next comming token.
*/

void	devour_token(t_token **tok_lst)
{
	t_token	*tmp;

	tmp = *tok_lst;
	if (*tok_lst == NULL)
		return ;
	*tok_lst = (*tok_lst)->next;
	garbage_free((void **)&tmp->data);
	garbage_free((void **)&tmp);
}

bool	check_errors(t_token *tok_lst)
{
	if (tok_lst == NULL)
	{
		write(2, SYNTAX_ERROR, sizeof(SYNTAX_ERROR));
		return (false);
	}
	if (tok_lst->type == OP_PARENTH_TOKEN)
		return (false);
	return (true);
}

bool	devour_token_and_return_false(t_token **tok_lst)
{
	devour_token(tok_lst);
	return (false);
}


static t_token	*get_before_matching_parenth(t_token *tok_lst)
{
	int		parenth_count;
	t_token	*previous;

	parenth_count = 1;
	previous = tok_lst;
	tok_lst = tok_lst->next;
	while (tok_lst != NULL)
	{
		if (tok_lst->type == OP_PARENTH_TOKEN)
			++parenth_count;
		else if (tok_lst->type == CLOSE_PARENTH_TOKEN)
		{
			--parenth_count;
			if (parenth_count == 0)
				return (previous);
		}
		previous = tok_lst;
		tok_lst = tok_lst->next;
	}
	return (NULL);
}

/*
** Free the tok_lst token linked list using the garbage_free function
*/

void	clear_tokens(t_token **tok_lst)
{
	t_token	*prev;
	t_token	*current;

	if (*tok_lst == NULL)
		return ;
	current = *tok_lst;
	while (current)
	{
		garbage_free((void **)&current->data);
		prev = current;
		current = current->next;
		garbage_free((void **)&prev);
	}
	*tok_lst = NULL;
}

/*
** Returns true if the token is a redirection. Otherwise, returns false.
*/

bool	is_redirection(enum e_token_type type)
{
	return (type == LESSER_TOKEN || type == DOUBLE_LESSER_TOKEN
		|| type == GREATER_TOKEN || type == DOUBLE_GREATER_TOKEN);
}

/*
** Returns true if the token is part of a simple command. Otherwise, returns
** false.
*/


bool	is_leaf(enum e_token_type type)
{
	return (is_redirection(type) == true || type == WORD_TOKEN);
}

bool	check_errors_and_build_sub_tree(
		t_token **tok_lst, t_token **sub_tok_lst, t_node **sub_tree)
{
	if ((*tok_lst != NULL
			&& (is_leaf((*tok_lst)->type) == true
				|| (*tok_lst)->type == OP_PARENTH_TOKEN))
		|| build_abstract_syntax_tree(sub_tok_lst, sub_tree, true) == false)
	{
		clear_tokens(sub_tok_lst);
		return (false);
	}
	return (true);
}


bool	print_error_and_return(t_token *token)
{
	if (token == NULL)
		write(2, SYNTAX_ERROR, sizeof(SYNTAX_ERROR));
	else
		write(2, SYNTAX_ERROR_LEX, sizeof(SYNTAX_ERROR_LEX));
	return (false);
}

bool	parse_parenthesis(t_token **tok_lst, t_node **ast)
{
	t_token	*before_matching_parenth;
	t_node	*sub_tree;
	t_token	*sub_tok_lst;

	if ((*tok_lst)->next != NULL && (*tok_lst)->next->type == CLOSE_PARENTH_TOKEN)
		return (devour_token_and_return_false(tok_lst));
	before_matching_parenth = get_before_matching_parenth(*tok_lst);
	devour_token(tok_lst);
	if (before_matching_parenth == NULL)
	{
		clear_tokens(tok_lst);
		return (print_error_and_return(*tok_lst));
	}
	sub_tok_lst = *tok_lst;
	*tok_lst = before_matching_parenth->next->next;
	garbage_free((void **)&before_matching_parenth->next->data);
	garbage_free((void **)&before_matching_parenth->next);
	if (check_errors_and_build_sub_tree(tok_lst, &sub_tok_lst, &sub_tree)
		== false)
		return (false);
	clear_tokens(&sub_tok_lst);
	*ast = sub_tree;
	if (*tok_lst != NULL && (*tok_lst)->type == PIPE_TOKEN)
		return (false);
	return (true);
}


unsigned int	get_nb_args(t_token *tok_lst)
{
	unsigned int	nb_args;
	t_token			*current;

	nb_args = 0;
	current = tok_lst;
	while (current != NULL && is_leaf(current->type) == true)
	{
		++nb_args;
		current = current->next;
	}
	return (nb_args);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		size;
	char	*dup;

	i = 0;
	if (s == NULL)
		size = 1;
	else
		size = ft_strlen(s);
	dup = garbage_malloc(sizeof(char) * (size + 1));
	if (s != NULL)
	{
		while (s[i])
		{
			dup[i] = s[i];
			i++;
		}
	}
	dup[i] = '\0';
	return (dup);
}

bool	print_error_and_return_false(bool is_subshell)
{
	if (is_subshell == false)
		write(2, SYNTAX_ERROR, sizeof(SYNTAX_ERROR));
	else
		write(2, SYNTAX_ERROR_LEX, sizeof(SYNTAX_ERROR_LEX));
	return (false);
}

/*
** The from_lst_to_array() function will malloc and fill the argv array of
** strings containing the arguments of the command.
*/

static bool	from_lst_to_array(
			t_token **tok_lst, t_node *simple_cmd, bool is_subshell)
{
	int	i;

	i = 0;
	simple_cmd->content.simple_cmd.argv = garbage_malloc(sizeof(char *)
			* (get_nb_args(*tok_lst) + 1));
	ft_bzero(simple_cmd->content.simple_cmd.argv,
		sizeof(simple_cmd->content.simple_cmd.argv));
	while (*tok_lst != NULL && is_leaf((*tok_lst)->type) == true)
	{
		if (is_redirection((*tok_lst)->type) == true
			&& ((*tok_lst)->next == NULL || (*tok_lst)->next->type != WORD_TOKEN))
		{
			devour_token(tok_lst);
			if (*tok_lst == NULL)
				return (print_error_and_return_false(is_subshell));
			if ((*tok_lst)->type != WORD_TOKEN)
				return (false);
		}
		simple_cmd->content.simple_cmd.argv[i++] = ft_strdup((*tok_lst)->data);
		devour_token(tok_lst);
	}
	simple_cmd->content.simple_cmd.argv[i] = NULL;
	return (true);
}

/*
** Parsing a simple command is done the following way:
** - if the token is not a leaf, it is a syntax error: false is returned;
** - the simple_command node is maloced;
** - the number of arguments of the command is obtained with get_argc();
** - from_lst_to_array() fills the argv array.
*/

bool	parse_simple_cmd(t_token **tok_lst, t_node **ast, bool is_subshell)
{
	t_node	*simple_cmd;

	if ((*tok_lst)->type == CLOSE_PARENTH_TOKEN)
		return (false);
	else if ((*tok_lst)->type == OP_PARENTH_TOKEN)
		return (parse_parenthesis(tok_lst, ast));
	if (is_leaf((*tok_lst)->type) == false)
		return (false);
	simple_cmd = NULL;
	simple_cmd = garbage_malloc(sizeof(*simple_cmd));
	ft_bzero(simple_cmd, sizeof(*simple_cmd));
	simple_cmd->type = SIMPLE_CMD;
	simple_cmd->content.simple_cmd.fd_in = STDIN_FILENO;
	simple_cmd->content.simple_cmd.fd_out = STDOUT_FILENO;
	if (from_lst_to_array(tok_lst, simple_cmd, is_subshell) == false)
		return (false);
	*ast = simple_cmd;
	return (true);
}

/*
** A pipeline is made of at least one simple command. If a pipe token is found
** after a first command, parse_pipeline() will loop on the following steps
** as long as the next coming token is not a pipe:
** - the pipe token is eaten;
** - if the token linked list is empty, it is an error: false is returned;
** - the pipe node in malloced and initialized;
** - the AST is transfered to the left part of the pipe_node and the
** parse_simple_cmd() function is called on the right child of the pipe_node.
** On success, true is returned.
*/

bool	parse_pipeline(t_token **tok_lst, t_node **ast, bool is_subshell)
{
	t_node	*pipe_node;
	t_node	*simple_cmd;

	if (parse_simple_cmd(tok_lst, &simple_cmd, is_subshell) == false)
		return (false);
	*ast = simple_cmd;
	while (*tok_lst != NULL && (*tok_lst)->type == PIPE_TOKEN)
	{
		devour_token(tok_lst);
		if (check_errors(*tok_lst) == false)
			return (false);
		pipe_node = NULL;
		pipe_node = garbage_malloc(sizeof(*pipe_node));
		ft_bzero(pipe_node, sizeof(*pipe_node));
		pipe_node->type = PIPE_NODE;
		pipe_node->content.child.left = *ast;
		*ast = pipe_node;
		if (parse_simple_cmd(
				tok_lst, &((*ast)->content.child.right), is_subshell) == false)
			return (false);
	}
	return (true);
	
}
/*
** To parse a logical operator, the corresponding node is created, the AST is
** transfered to the left child of the node, and the parse_pipeline() function
** is called to add the following command to the right child of the node. The
** AST is the set ot point to the node.
*/

bool	parse_logical_operator(
		t_token **tok_lst, t_node **ast, bool is_subshell)
{
	t_node	*separator_node;

	if (*ast == NULL)
		return (false);
	separator_node = NULL;
	separator_node = garbage_malloc(sizeof(*separator_node));
	ft_bzero(separator_node, sizeof(*separator_node));
	separator_node->type = (enum e_node_type)((*tok_lst)->type);
	separator_node->content.child.left = *ast;
	*ast = separator_node;
	devour_token(tok_lst);
	if (*tok_lst == NULL)
	{
		if (separator_node->type == SEMICO_NODE)
			return (true);
		else
		{
			write(2, SYNTAX_ERROR, sizeof(SYNTAX_ERROR));
			return (false);
		}
	}
	return (parse_pipeline(
			tok_lst, &(separator_node->content.child.right), is_subshell));
}

/*
** Once the lexing phase is done, the token linked list is processed by the
** build_ast() function to build the Abstract Syntax Tree that will be finally
** executed in the shell loop.
** Depending on the token met in the tok_lst token linked list, the proper
** parser is called untill the tok_lst token list is empty or until a closing
** parenthesis is encountered (this is because build_ast() is recursively called
** by the parse_parenthsis() function, see parse_parenthesis.c for further
** informations.
** On success, build_ast() return true, false otherwise.
*/

bool	build_abstract_syntax_tree(t_token **tok_lst, t_node **ast, bool is_subshell)
{
	bool	ret;

	ret = true;
	while (*tok_lst != NULL)
	{
		if (is_logical_operator((*tok_lst)->type) == true)
		{
			if (*ast == NULL)
				return (false);
			ret = parse_logical_operator(tok_lst, ast, is_subshell);
		}
		else
			ret = parse_pipeline(tok_lst, ast, is_subshell);
		if (ret == false)
			return (false);
	}
	return (true);
}

/*
 * Initialize structs with NULL and Lex/Parse
*/

t_node	*ft_lex_parse(char *line)
{
	t_node	*ast;
	t_token	*token_list;

	ast = NULL;
	token_list = NULL;
	if (lexer(line, &token_list) == true)
	{
		printf("LEXER RETURN VALUE : %d\n", lexer(line, &token_list));
		printf("i have to build my ast next\n");
		if (build_abstract_syntax_tree(&token_list, &ast, false) == false || token_list != NULL)
		{
			if (token_list != NULL)
				write(2, SYNTAX_ERROR_LEX, sizeof(SYNTAX_ERROR_LEX));
			printf("To be continued\n");
		}
	}
	else
	{
		printf("LEXER RETURN VALUE : %d\n", lexer(line, &token_list));
		write(2, "To be continued", sizeof("To be continued"));
		exit(EXIT_FAILURE);
	}
	return (ast);
}

/*
 * Function to save history using readline/history.h
*/

void	ft_add_history(char *line)
{
	add_history(line);
}

/*
 * parse commands and executes them
*/

void	ft_executor(char *line, bool inline_mode)
{
	t_node	*ast;
	//printf("line = %s\ninline_mode = %d\n", line, inline_mode);
	ast = NULL;
	if (line != NULL)
	{
		ft_add_history(line);
		ast = ft_lex_parse(line);
	}
	else
	{
		printf("To be continued :) \n");
		exit(EXIT_FAILURE);
	}
}

/*
 * Mandatory function : read command line using readline(),
 * and execute it
*/

void	minishell(bool inline_mode)
{
	char	*line;

	while (true)
	{
		line = read_line(inline_mode);
		ft_executor(line, inline_mode);
	}
}

/*
 * Free all filedescriptors beyond two
*/

void	ft_free_fd(void)
{
	int	fd;

	fd = open("console", O_WRONLY);
	while (fd >= 0)
	{
		if (fd >= 3)
			close(fd);
		break;
	}
}

/*
 * Init minishell && launch all processes
 * Our executable should not accept arguments dynamically
 * if argc == 1 : launch program
 * else : ERROR
*/

int	main(int argc, char **argv, char **env)
{
	bool	inline_mode;

	if (argc == 1)
	{
		//ft_print_envp(env);
		ft_free_fd();
		minishell(inline_mode);
	}
	else
	{
		write(2, ERROR_MINISHELL, sizeof(ERROR_MINISHELL));
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
