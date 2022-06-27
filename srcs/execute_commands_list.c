/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:54:29 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/27 16:19:48 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_semicolon_node(t_node *ast)
{
	execute_ast_data(ast->content.child.left);
	if (ast->content.child.right != 0x0)
		execute_ast_data(ast->content.child.right);
}

void	execute_logical_or_node(t_node *ast)
{
	execute_ast_data(ast->content.child.left);
	if (*retrieve_exit_status() != 0x0)
		execute_ast_data(ast);
}

void	execute_logical_and_node(t_node *ast)
{
	execute_ast_data(ast->content.child.left);
		if (*retrieve_exit_status() == 0x0)
			execute_ast_data(ast->content.child.right);
}

void	execute_commands_list(t_node *ast)
{
	if (ast->type == AND_NODE)
		execute_logical_and_node(ast);
	else if (ast->type == OR_NODE)
		execute_logical_or_node(ast);
	else
		execute_semicolon_node(ast);
}
