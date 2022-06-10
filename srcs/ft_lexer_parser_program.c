/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_parser_program.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:40:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/09 23:35:10 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * STEP 00 : Init my token list with NULL [type t_token], for futher 
 * infos look at../includes/minishell.h [LEXER ABTRACTION] section.
 * STEP 01 : Call the function consturctor_token_list() to build my tokens,
 * respecting LEXER grammar.
 * STEP 02 : Init my AST with NULL in order to build it after tokenizing,
 * ast_constructor() function with be responsible of that, so we represent
 * data in memory.
*/

t_node	*ft_lexer_parser_program(char *line)
{
	t_node	*ast;
	t_token	*token_list;
	t_token	*tmp;

	ast = 0x0;
	token_list = 0x0;
	if (constructor_token_list(line, &token_list) == true)
	{
		ft_print_token(token_list);
		printf("\n\nBuilding TOKEN LIST ...\n\n");
		sleep(1);
		//if (ast_constructor(&token_list, &ast, false) == false || \
				token_list != 0x0 )
		//{
		//	if (token_list != 0x0)
		//	{
		//		printf("To be continued ...\n");
		//	}
		//}
		
	}
	else
		printf("To be continued ...\n");
	return (ast);
}
