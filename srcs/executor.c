/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/08 16:32:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function to save history input from stdin in our CLI.
*/

void	ft_add_history(char *line)
{
	add_history(line);
}

/*
 * initialize my AST, lex and parse [Syntax analyzer] the input read,
 * Build my ASY and execute it.
*/

void	ft_executor(char *line, bool inline_mode)
{
	t_node	*ast;

	ast = 0x0;
	if (line != 0x0)
	{
		ft_add_history(line);
		ast = ft_lexer_parser_program(line);
		{
			if (ast != 0x0)
				printf("To be continued ...\n");
		}
	}
	else
	{
		printf("To be continued ...\n");
		exit(EXIT_FAILURE);
	}
}
