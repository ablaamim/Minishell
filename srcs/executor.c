/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/11 09:46:10 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		ast = ft_lexer_parser_program(line);
		{
			if (ast != 0x0)
			{
				execute_ast_data(ast);
				ast_clearing(&ast);
			}
		}
	}
}
