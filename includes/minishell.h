/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:06:31 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/09 16:46:07 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

/*
 * error defines
*/

# define ARGV_ERROR "Error : invalid argument\n"
# define WARNING "Error : outline mode\n"
# define MALLOC_ERROR "Error : malloc() failed to allocate memory\n"
# define ERROR_MINISHELL_EOF "minishell : syntax error, unexpected eof\n"
/*
 * LEXER ABSTRACTION.
*/

/*
 * Must contain all char types, during the lexing phase the proper
 * Tokenizer will be called accordingly to the type encountred.
*/

enum e_char_type
{
	ANY_CHAR,
	NULL_CHAR,
	SPACE_CHAR,
	SQUOTE_CHAR,
	DQUOTE_CHAR,
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
 * All types of tokens handled by the prgram.
*/

enum e_token_type
{
	WORD_TOKEN,
	PIPE_TOKEN,
	OR_TOKEN,
	AND_TOKEN,
	SEMICO_TOKEN,
	LESSER_TOKEN,
	DLESSER_TOKEN,
	GREATER_TOKEN,
	DGREATER_TOKEN,
	AMPERSAND_TOKEN,
	OP_PARENTH_TOKEN,
	CLOSE_PARENTH_TOKEN,
};

/*
 * Word token rules, its either accepted or not_accepted.
*/

enum e_char_rules
{
	NOT_ACCEPTED,
	ACCEPTED
};

/*
 * Finally we need a tokens linked list.
*/

typedef struct s_token
{
	char				*data;
	enum e_token_type	type;
	struct s_token		*next;
}	t_token;

/*
 * PARSER ABSTRACTION
*/

/*
 * All code types of nodes that can be found in our AST,
 * leaves are considered as nodes.
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
 * All possible types of redirection that we can encounter in a simple
 * command
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
 * Simple command, it can be composed of options (arguments), i/o stream
 * and quotes (single / double).
*/

typedef struct s_simple_cmd
{
	char	**argv;
	int		fd_in;
	int		fd_out;
	bool	input_stream_has_quotes;
}	t_simple_cmd;

/*
 * A node in our AST, it always has children, one on the left,
 * and one on the right.
*/

typedef struct s_child
{
	struct s_node	*left;
	struct s_node	*right;
}	t_child;

/*
 * A member of the AST that contains a node_type and a content,
 * which can be a simple command or a child.
*/

typedef union u_node_content
{
	struct s_simple_cmd	simple_cmd;
	struct s_child		child;
}	t_node_content;

/*
 * A member of the AST (node) contains a node_type and a content which can
 * be a simple command or a child.
*/

typedef struct s_node
{
	enum e_node_type	type;
	t_node_content		content;
}	t_node;

/*
 * Garbage memory collection data struct, it is a linked list.
*/

typedef struct s_garbage_list
{
	void					*ptr;
	struct s_garbage_list	*next;
}	t_garbage_list;

/*
 * Main funnctions.
*/

void				ft_minishell(bool inline_mode);
char				*ft_prompt(bool inline_mode);
char				*read_line(bool inline_mode);
void				ft_executor(char *line, bool inline_mode);
void				ft_add_history(char *line);

/*
 * Functions to debug and track states of output :
*/

void				ft_print_env(char **env);
void				ft_print_token(t_token *token);
/*
 * LEXER FUNCTIONS :
*/

t_node				*ft_lexer_parser_program(char *line);
bool				constructor_token_list(char *in_characters, \
		t_token **token_list);
t_token				*retrieve_next_token(char *in_characters, int *i);
t_token				*tokenize_word(char *in_characters, int *i);
enum e_char_type	define_char_type(char c);
enum e_char_rules	apply_rules(enum e_char_type char_types);
t_token				*token_generator(char *data, enum e_token_type type);
void				append_token(t_token *new_token, t_token **token_list);
/*
 * Garbage Memory collection functions, to allocate, initialize, delete...
*/

void				*garbage_malloc(size_t size);
t_garbage_list		**get_garbage_list(void);
void				garbage_bzero(void *memory, size_t n);
void				garbage_memdel(void **memory);
void				garbage_free(void **garbage_to_free);

/*
 * PARSER FUNCTIONS :
*/

bool				ast_constructor(t_token **token_list, t_node **ast, \
		bool is_subshell); //[To be continued]

/*
 * Libft utils :
*/

char				*ft_strndup(const char *str, size_t n);
size_t				ft_strnlen(char const *str, size_t max_len);
void				*ft_memcpy(void *dest, void const *src, size_t n);

#endif
