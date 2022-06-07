/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:06:31 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/07 17:28:46 by ablaamim         ###   ########.fr       */
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
	GREAT_CHAR,
	SEMICO_CHAR,
	PIPE_CHAR,
	NB_CHAR_TYPE
};

/*
 * All types of tokens handled by the prgram.
*/

enum e_token_type
{
	WORD_TOKEN,
	PIPE_TOKEN,
	SEMICO_TOKEN,
	GREATER_TOKEN
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
	SEMICO_NODE
};

/*
 * All possible types of redirection that we can encounter in a simple
 * command. [To be continued]
*/

enum e_redirection_type
{
	OUTPUT_REDIR,
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
 * Main funnctions.
*/

int		main(int argc, char **argv, char **env);
void	ft_minishell(bool inline_mode);
char	*ft_prompt(bool inline_mode);
char	*read_line(bool inline_mode);
void	ft_executor(char *line, bool inline_mode);
void	ft_add_history(char *line);

/*
 * Functions to debug states of output
*/

void	ft_print_env(char **env);
void	ft_display_ast(t_node *ast, int level);

/*
 * Function responsible of initializing my AST, then build it.
*/

t_node *ft_lexer_parser_program(char *line);

#endif
