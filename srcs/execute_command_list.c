/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:19:10 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/21 16:50:38 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_and_node(t_node *node)
{
	ft_iterate_tree(node->content.child.left, 0, 0, 0x0);
		if (*retrieve_exit_status() == 0x0)
			ft_iterate_tree(node->content.child.right, 0, 0, 0x0);
}

void	execute_or_node(t_node *node)
{
	ft_iterate_tree(node->content.child.right, 0, 0, 0x0);
		if (*retrieve_exit_status() != 0x0)
			ft_iterate_tree(node->content.child.left, 0, 0, 0x0);
}

void	execute_semicolon_node(t_node *node)
{
	ft_iterate_tree(node->content.child.left, 0, 0, 0x0);
		if (node->content.child.right != 0x0)
			ft_iterate_tree(node->content.child.right, 0, 0, 0x0);
}

void	execute_command_list(t_node *node)
{
	if (node->type == AND_NODE)
		execute_and_node(node);
	else if (node->type == OR_NODE)
		execute_or_node(node);
	else
		execute_semicolon_node(node);
}
