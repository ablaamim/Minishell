/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/23 23:50:18 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * read_line function reads from input using readline, saves it in a char *
 * then it returns it to be used in next program
*/

char	*read_line()
{
	char	*line;

	line = readline("Minishell$>");
	if (line == 0x0 && line[0] == EOF)
	{
		variadic_error_printer(2, "Error : CTRL + D Should be handled\n");
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

void	ft_minishell()
{
	char	*line;

	while (true)
	{
		line = read_line();
		ft_executor(line);
	}
}
