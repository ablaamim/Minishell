/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 22:12:39 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/20 13:09:02 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * - IF FD CONTENT IS -1 CLOSE FD.
 * - ELSE EXEC.
*/

bool	is_redirection(char **arguments, int *fd_input, int *fd_output, \
		bool input_has_quotes)
{
	if (ft_strcmp("<", *arguments) == 0x0)
	{
		if (*fd_input != 0x0)
			close(*fd_input);
		*fd_input = input_stream_redirection(*(arguments + 1));
		if (*fd_input == -1)
			return (false);
	}
	else
	{
		if (*fd_output != 0x0)
			close(*fd_output);
		/*
		 * TO DO :
		 *
		 * HANDLE OUTPUT REDIRECTIONS
		*/
		//*fd_output = output_stream_redirection());
		if (*fd_output == -1)
			return (false);
	}
	/*
	 * TO DO :
	 *
	 * HANDLE HEREDOC.
	*/
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
		}
		else
			++i;
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
		return (scan_open__redirections(ast->content.simple_cmd.argv, \
					&ast->content.simple_cmd.fd_in, \
					&ast->content.simple_cmd.fd_out, \
					ast->content.simple_cmd.input_has_quotes));
	}
	else
	{
		/*
		 * TO DO :
		 *
		 * EXEC REDIRECTIONS ON LEFT AND RIGHT OF THE AST.
		*/
		return (true);
	}
}
