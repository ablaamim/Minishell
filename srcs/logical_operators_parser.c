/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operators_parser.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:38:25 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/29 17:44:20 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * To parse a logical operator, the corresponding node is created, the AST is
 * transfered to the left child of the node, and the pipeline_parser() function
 * will be called to add the following command to the right child of the node.
*/

bool	logical_operators_parser(t_token **token_list, t_node **ast, \
		bool is_subshell)
{
	t_node	*node_separator;

	if (*ast == 0x0)
		return (false);
	node_separator = 0x0;
	node_separator = garbage_malloc(sizeof(*node_separator));
	ft_bzero(node_separator, sizeof(*node_separator));
	node_separator->type = (enum e_node_type) ((*token_list)->type);
	node_separator->content.child.left = *ast;
	*ast = node_separator;
	token_devour(token_list);
	if (*token_list == 0x0)
	{
		if (node_separator->type == SEMICO_NODE)
			return (true);
		else
		{
			write(2, ERROR_MINISHELL_EOF, sizeof(ERROR_MINISHELL_EOF));
			return (false);
		}
	}
	return (pipe_parser(token_list, &(node_separator->content.child.right), \
				is_subshell));
}
