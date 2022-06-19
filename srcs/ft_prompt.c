/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/19 16:26:04 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * read_line function reads from input using readline, saves it in a char *
 * then it returns it to be used in next program
*/

char	*read_line(bool inline_mode)
{
	char	*line;

	line = NULL;
	if (inline_mode == false)
	{
		line = readline("Minishell$>");
		if (line == 0x0 && line[0] == EOF)
		{
			/*
			 * TO DO :
			 * Signal handling.
			*/
			variadic_error_printer(2, "Error : CTRL + D Should be handled\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/*
		 * TO DO :
		 * escape inprintable chars.
		*/
		variadic_error_printer(2, "Error : Escape inprintable lines.\n");
		exit(EXIT_FAILURE);
	}
	return (line);
}

/*
char	*ft_prompt(bool inline_mode)
{
	char	*line;

	line = 0x0;
	if (inline_mode == false)
	{
		line = read_line(inline_mode);
	}
	return (line);
}
*/

/*
 * Read command input via readline() inside the read_line program and runs
 * another program to continue the work
*/

void	ft_minishell(bool inline_mode)
{
	char	*line;

	while (true)
	{
		line = read_line(inline_mode);
		ft_executor(line, inline_mode);
		if (inline_mode == true)
			shell_exit(*retrieve_exit_status(), 0x0);
	}
}
