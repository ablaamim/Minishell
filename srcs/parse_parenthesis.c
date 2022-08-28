/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:49:52 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/28 12:17:07 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	display_error_and_return(t_token *token)
{
	if (token == NULL)
		variadic_error_printer(2,
			"minishell: syntax error: unexpected end of file\n");
	else
		variadic_error_printer(2,
			"minishell: syntax error near unexpected token `%s'\n",
			token->data);
	return (false);
}

t_token	*retrieve_before_matching_parenth(t_token *tok_lst)
{
	int		parenth_count;
	t_token	*previous;

	parenth_count = 1;
	previous = tok_lst;
	tok_lst = tok_lst->next;
	while (tok_lst != NULL)
	{
		if (tok_lst->type == OP_PARENTH_TOKEN)
			++parenth_count;
		else if (tok_lst->type == CLOSE_PARENTH_TOKEN)
		{
			--parenth_count;
			if (parenth_count == 0)
				return (previous);
		}
		previous = tok_lst;
		tok_lst = tok_lst->next;
	}
	return (NULL);
}

bool	verify_errors_and_build_sub_tree(
		t_token **token_list, t_token **sub_token_list, t_node **subtree)
{
	if ((*token_list != NULL
			&& (identify_leaf((*token_list)->type) == true
				|| (*token_list)->type == OP_PARENTH_TOKEN))
		|| ast_constructor(sub_token_list, subtree, true) == false)
	{
		tokens_clearing(sub_token_list);
		return (false);
	}
	return (true);
}

bool	devour_token_and_return_false(t_token **token_list)
{
	token_devour(token_list);
	return (false);
}

bool	parenthesis_parser(t_token **tkn_lst, t_node **ast)
{
	t_token	*before_matching_parenth;
	t_node	*sub_tree;
	t_token	*sub_token_list;

	if ((*tkn_lst)->next != NULL && (*tkn_lst)->next->type == OP_PARENTH_TOKEN)
		return (devour_token_and_return_false(tkn_lst));
	before_matching_parenth = retrieve_before_matching_parenth(*tkn_lst);
	token_devour(tkn_lst);
	if (before_matching_parenth == NULL)
	{
		tokens_clearing(tkn_lst);
		return (display_error_and_return(*tkn_lst));
	}
	sub_token_list = *tkn_lst;
	*tkn_lst = before_matching_parenth->next->next;
	garbage_free((void **)&before_matching_parenth->next->data);
	garbage_free((void **)&before_matching_parenth->next);
	if (verify_errors_and_build_sub_tree(tkn_lst, &sub_token_list, &sub_tree)
		== false)
		return (false);
	tokens_clearing(&sub_token_list);
	*ast = sub_tree;
	if (*tkn_lst != NULL && (*tkn_lst)->type == PIPE_TOKEN)
		return (false);
	return (true);
}
