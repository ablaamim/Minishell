/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_parser_program.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:40:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/12 09:31:26 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * STEP 00 : Init my token list with NULL, for futher
 * infos look at../includes/minishell.h [LEXER ABTRACTION] section.
 * STEP 01 : Call the function consturctor_token_list() to build my tokens,
 * respecting LEXER grammar [Syntaxic analysis].
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
		printf("Welcome to minishell program !\n\n");
		sleep(1);
		printf("LINKED LIST OF TOKENS : \n\n");
		ft_print_token(token_list);
		if (ast_constructor(&token_list, &ast, false) == false || \
				token_list != 0x0 )
		{
			//if (ast == 0x0)
			//	printf("YOU FUCKED UP PLENTY !!");
			if (token_list != 0x0)
				write(2, ERROR_TOKEN, sizeof(ERROR_TOKEN));
			//printf("to be continued ...\n");
			exit(EXIT_FAILURE);
		}
		
	}
	else
		printf("To be continued [STAGE 01]...\n");
	printf("\n\nBuilding AST ...\n\n");
	sleep(1);
	disp_tree(ast, 0);
	return (ast);
}
