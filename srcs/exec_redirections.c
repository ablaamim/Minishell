/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:11:38 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/19 21:24:28 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * in simple_cmd there is data that you will need to manage redirections.
 * ->input_stream.
 * ->output_stream.
 * ->boolean value that determines if input stream has single or double quotes
 *
 * recursive calls would be good, just like your pipes akhay Moussa
 * Ghadi nbda wkmel nta.
*/

bool	execute_redirections(t_node *node)
{
	if (node->type == SIMPLE_CMD)
	{
		printf("Manage redirections\n");
		return (true);
	}
	else
	{
		if (node->content.child.left != 0x0)
			if (execute_redirections(node->content.child.left) == false)
				return (false);
		if (node->content.child.right != 0x0)
			if (execute_redirections(node->content.child.right) == false)
				return (false);
		return (true);
	}
}
