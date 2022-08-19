/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:26:22 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/19 15:57:21 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * This function is elementary in all parsers during the building of my AST,
 * it devours the next token, by freeing the first token in token_list, and
 * it sets the head to the next element in token_list.
*/

void	token_devour(t_token **token_list)
{
	t_token	*temp;

	temp = *token_list;
	if (*token_list == 0x0)
		return ;
	*token_list = (*token_list)->next;
	free(temp->data);
	free(temp);
}

/*
* Once the lexing phase is finished, the built tokens linked list is
* processed by the ast_constructor(), the output of the constructor will
* be executed by the minishell loop.
* depending on the type of token met the proper parser will be called,
* untill the token linked list is fully scanned, or untill a closing
* parentheses is encountered, this is because the ast_constructor()
* will be recursively called by the parser_of_parentheses(),
* on success ast_constructor returns true, else false.
*/
bool	ast_constructor(t_token **token_list, t_node **ast, bool is_subshell)
{
	bool	return_value;

	return_value = true;
	while (*token_list != 0x0)
	{
		if (check_logical_operators((*token_list)->type) == true)
		{
			if (*ast == 0x0)
				return (false);
			return_value = logical_operators_parser(token_list, ast, \
					is_subshell);
		}
		else
			return_value = pipe_parser(token_list, ast, is_subshell);
		if (return_value == false)
			return (false);
	}
	return (true);
}
