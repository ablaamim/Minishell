/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_parser_program.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:40:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/08 17:47:10 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * STEP 00 : Init my token list with NULL [type t_token], for futher infos look at 
 * ../includes/minishell.h [LEXER ABTRACTION] section.
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

	ast = NULL;
	if (constructor_token_list(line, &token_list) == true)
	{
		printf("\nBuilding TOKEN LIST ...\n\n");
		sleep(2);
	}
	return (ast);
}
