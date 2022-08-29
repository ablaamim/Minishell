/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_parser_program.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:40:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/29 12:26:40 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * STEP 00 : Init my token list with NULL, for futher
 * infos look at../includes/minishell.h [LEXER ABTRACTION] section.
 *
 * STEP 01 : Call the function consturctor_token_list() to build my tokens,
 * respecting LEXER grammar AKA : Syntaxic analysis.
 *
 * STEP 02 : Init AST with NULL in order to build it after tokenizing,
 * its based on data contained inside the linked list.
 * ast_constructor() function with be responsible of that, so we represent
 * data in accessible memory.
 */

/*
 * BUGS I FOUND till now : a pipe without output command.
 *
 * $> ls | ls |
 *
 * $> segmentation fault.
 *
 * [CASE CLOSED] : if disp_tree() which is just a debuger is commented, segv
 * is eliminated
 *
 */

t_node	*ft_lexer_parser_program(char *line)
{
	t_node	*ast;
	t_token	*token_list;

	ast = 0x0;
	token_list = 0x0;
	if (constructor_token_list(line, &token_list) == true)
	{
		if (ast_constructor(&token_list, &ast, false) == false || \
				token_list != 0x0)
		{
			if (token_list != 0x0)
				variadic_error_printer(2, "%s : %s\n", ERROR_TOKEN, \
						token_list->data);
			exit_value_set(258);
			ast_clearing(&ast);
		}
	}
	else
		exit_value_set(SYNTAX_ERROR_EXIT);
	tokens_clearing(&token_list);
	return (ast);
}
