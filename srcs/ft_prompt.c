/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/27 16:08:55 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * read_line function reads from input using readline, saves it in a char *
 * then it returns it to be used in next program.
 * -> ALSO filter history.
*/

char	*read_line(void)
{
	char	*line;

	line = readline("Minishell$>");
	//if (get_next_line(0, &line) == -1 || ft_striter(line, &ft_isprint) \
			== 0x0)
	//	shell_exit(*retrieve_exit_status(), 0x0);
	return (line);
}

/*
 * Read command input via readline() inside the read_line program and runs
 * another program to continue the work
*/

void	ft_minishell(void)
{
	char	*line;

	while (true)
	{
		line = read_line();
		ft_executor(line);
	}
}
