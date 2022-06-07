/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/07 12:10:22 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function to save history in CLI
*/

void	ft_add_history(char *line)
{
	add_history(line);
}

/*
 * lex and parse [Syntax analyzer] the input read, and executes it
*/

void	ft_executor(char *line, bool inline_mode)
{
	if (line != 0x0)
	{
		ft_add_history(line);
	}
	else
	{
		printf("To be continued ...\n");
		exit(EXIT_FAILURE);
	}
}
