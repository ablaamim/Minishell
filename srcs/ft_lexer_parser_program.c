/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_parser_program.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:40:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/07 19:31:56 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * STEP 00 : Init my token list with NULL, for futher
 * infos look at../includes/minishell.h [LEXER ABTRACTION] section.
 * STEP 01 : Call the function consturctor_token_list() to build my tokens,
 * respecting LEXER grammar AKA : Syntaxic analysis.
 * STEP 02 : Init my AST with NULL in order to build it after tokenizing,
 * its based ondata contained inside the linked list.
 * ast_constructor() function with be responsible of that, so we represent
 * data in memory.
*/

t_node	*ft_lexer_parser_program(char *line)
{
	t_node	*ast;
	t_token	*token_list;

	ast = 0x0;
	token_list = 0x0;
	if (constructor_token_list(line, &token_list) == true)
	{
		printf("===========> Welcome to minishell program <=============\n\n");
		printf("===============> LINKED LIST OF TOKENS <================\n\n");
		ft_print_token(token_list);
		if (ast_constructor(&token_list, &ast, false) == false || \
				token_list != 0x0 )
		{
			if (token_list != 0x0)
			{
				printf("\n\nERROR INSIDE AST CONSTRUCTOR\n\n");
				variadic_error_printer(2, "\nMinishell : Syntax error near unexpected token %s\n", token_list->data);
			}
			exit_value_set(SYNTAX_ERROR_EXIT);
			ast_clearing(&ast);
		}
	}
	else
		exit_value_set(SYNTAX_ERROR_EXIT);
	tokens_clearing(&token_list);
	printf("====================> DISPLAY TREE <========================\n\n");
	disp_tree(ast, 0); // FOR DEBUG RIGHT NOW.
	return (ast);
}
