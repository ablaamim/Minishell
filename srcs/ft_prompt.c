/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/07 12:42:55 by ablaamim         ###   ########.fr       */
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
		if (!line && line[0] == EOF)
		{
			printf("END OF FILE ENCOUNTRED\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		write(2, "ERROR", sizeof("ERROR"));
		exit(EXIT_FAILURE);
	}
	return (line);
}

char	*ft_prompt(bool inline_mode)
{
	char	*line;

	line = read_line(inline_mode);
	return (line);
}

/*
 * Read command input via readline() inside the read_line program and runs
 * another program to continue the work
*/

void	ft_minishell(bool inline_mode)
{
	char	*line;

	while (true)
	{
		line = ft_prompt(inline_mode);
		ft_executor(line, inline_mode);
	}
}
