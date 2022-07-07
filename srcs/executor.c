/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/07 09:55:49 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function to save history input from stdin in my CLI, without termcaps.
*/

void	ft_add_history(char *line)
{
	add_history(line);
}

/*
 * Initialize my AST, lex and parse [Syntax analyzer + Recursive descent 
 * parser] the input read.
 * Then build my AST and execute it.
*/

void	ft_executor(char *line)
{
	t_node	*ast;

	ast = 0x0;
	if (line != 0x0)
	{
		ft_add_history(line);
		ast = ft_lexer_parser_program(line);
		{
			if (ast != 0x0)
			{
				printf("\n\n================> EXECUTION GONE PRRRRR : <=================\n\n");
				execute_ast_data(ast);
				ast_clearing(&ast);
			}
		}
	}
}
