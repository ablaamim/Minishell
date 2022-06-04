/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_one_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:21:52 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/05 00:47:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

#define ERROR_MINISHELL "Error : exit minishell\n"
#define WARNING "NOT INLINE MODE\n!!!!!!"

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
		if (!line)
			return (NULL);
		//add_history(line);
	}
	else
		write(2, WARNING, sizeof(WARNING));
	return (line);
}

/*
 * Lexer / Parser
*/

t_node	*lexer_parser(char *line)
{
	t_node	*ast;
}

/*
 * Save history, parse commands and executes them
*/

void	execution(char *line, bool inline_mode)
{
	t_node	*ast;
	//printf("line = %s\ninline_mode = %d\n", line, inline_mode);
	if (line != NULL)
	{
		add_history(line);
		ast = lexer_parser(line);
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
		execution(line, inline_mode);
	}
}

/*
 * Init minishell && launch all processes
*/

int	main(int argc, char **argv, char **env)
{
	bool	inline_mode;

	if (argc == 1)
	{
		//ft_print_envp(env);
		minishell(inline_mode);
	}
	else
	{
		write(2, ERROR_MINISHELL, sizeof(ERROR_MINISHELL));
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
