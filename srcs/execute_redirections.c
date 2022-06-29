/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 22:12:39 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/29 16:14:35 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Delete redirections from argv content.
*/

void	delete_redirections_in_argv(char **arguments)
{
	int	i;

	i = 2;
	while (arguments[i] != 0x0)
	{
		arguments[i - 2] = arguments[i];
		++i;
	}
	arguments[i - 2] = arguments[i];
}

/*
 * - IF FD CONTENT IS -1 CLOSE FD.
 * - ELSE EXEC.
*/

bool	is_redirection(char **arguments, int *fd_input, int *fd_output, \
		bool input_has_quotes)
{
	//printf("Salam!!\n\n");
	if (ft_strcmp("<", *arguments) == 0x0)
	{
		//printf("FD_INPUT = %d\n\n", *fd_input);
		if (*fd_input != 0x0)
			close(*fd_input);
		*fd_input = input_stream_redirection(*(arguments + 1));
		if (*fd_input == -1)
			return (false);
	}
	else if (ft_strcmp("<<", *arguments) == 0x0)
	{
		if (*fd_input != 0x0)
			close(*fd_input);
		*fd_input = heredoc_redir(*(arguments + 1), \
				input_has_quotes);
		if (*fd_input == -1)
			return (false);
	}
	else
	{
		if (*fd_output != 1)
			close(*fd_output);
		*fd_output = output_stream_redirection(arguments);
		if (*fd_output == -1)
			return (false);
	}
	return (true);
}

/*
 * Check if arguments content is redirected.
*/

bool	arg_content_is_redirected(char *arguments)
{
	/*
	 * AUTOMATE TRANSITION OF THE SCANNER AUTOMATA.
	*/
	return(ft_strcmp(">", arguments) == 0x0 || ft_strcmp("<", arguments) == \
			0x0 || ft_strcmp(">>", arguments) == 0x0 || ft_strcmp("<<", \
				arguments) == 0x0);
}

/*
 * Scan argv for redirections and close file descriptors.
*/

bool	scan_open_redirections(char **argv, int *fd_input, int *fd_output, \
		bool input_has_quotes)
{
	int	i;

	i = 0x0;
	/*
	 * SCANNER AUTOMATA
	*/
	//printf("ARE YOU OK ?\n\n");
	while (argv[i] != 0x0)
	{
		if (arg_content_is_redirected(argv[i]) == true)
		{
			/*
			 * File Name normalization it should not exceed 255 chars.
			*/
			if (ft_strlen(argv[i + 1]) > 255)
			{
				variadic_error_printer(2, "Minishell : %s : File name is too \
						long\n", argv[i + 1]);
				return (false);
			}
			if (is_redirection(&argv[i], fd_input, fd_output, input_has_quotes\
						) == false)
				return (false);
			delete_redirections_in_argv(&argv[i]);
		}
		else
			++i;
		//printf("IS SCAN AUTOMATA OK ??\n\n");
	}
	return (true);
}

/*
 * Function that execute redirections in simple command.
*/

bool	execute_redirections(t_node *ast)
{
	if (ast->type == SIMPLE_CMD)
	{
		//printf("ARE YOU OK ??\n\n");
		return (scan_open_redirections(ast->content.simple_cmd.argv, \
					&ast->content.simple_cmd.fd_in, \
					&ast->content.simple_cmd.fd_out, \
					ast->content.simple_cmd.input_has_quotes));
	}
	else
	{
		/*
		 * TO DO :
		 *
		 * EXEC REDIRECTIONS ON LEFT AND RIGHT OF THE AST RECURSIVELY.
		*/
		if (ast->content.child.left != 0x0)
			if (execute_redirections(ast->content.child.left) == false)
				return (false);
		if (ast->content.child.right != 0x0)
			if (execute_redirections(ast->content.child.right) == false)
				return (false);
		return (true);
	}
}
