/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/18 22:53:26 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Initialize AST, lex and parse [Syntax analyzer + 
 * Recursive descent parser] the input read.
 * Then build AST.
 *
 * bistami task : execute AST.
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
				/*
				 * This is where you will execute the AST akhay moussa.
				 * anhayd had thrash functions.
				*/
				//execute_ast_data(ast);
				//ast_clearing(&ast);
			}
		}
	}
}
