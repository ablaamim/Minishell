/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:19:10 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 01:32:45 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_and_node(t_node *node, t_pipe **pipe_, int *exec_index)
{
	ft_iterate_tree(node->content.child.left, pipe_, exec_index);
	ft_handle_reset(pipe_, exec_index);
	if (*retrieve_exit_status() == 0)
		ft_iterate_tree(node->content.child.right, pipe_, exec_index);
}

void execute_or_node(t_node *node, t_pipe **pipe_, int *exec_index)
{
	ft_iterate_tree(node->content.child.left, pipe_, exec_index);
	ft_handle_reset(pipe_, exec_index);
	if (*retrieve_exit_status() != 0)
		ft_iterate_tree(node->content.child.right, pipe_, exec_index);
}

void execute_semicolon_node(t_node *node, t_pipe **pipe_, int *exec_index)
{
	if (node->content.child.left)
		ft_iterate_tree(node->content.child.left, pipe_, exec_index);
	ft_handle_reset(pipe_, exec_index);
	if (node->content.child.right)
		ft_iterate_tree(node->content.child.right, pipe_, exec_index);
}

void execute_pipe(t_node *node, t_pipe **pipe_, int *exec_index, int fd[2])
{
	if (pipe(fd) == ERR)
		shell_exit(EXIT_FAILURE, strerror(errno));
	ft_lstadd_front(pipe_, ft_lstnew(fd));
	ft_iterate_tree(node->content.child.left, pipe_, exec_index);
	ft_iterate_tree(node->content.child.right, pipe_, exec_index);
}

void ft_hanlde_iteration(t_node *node, t_pipe **pipe_, int *exec_index)
{
	int fd[2];

	if (node->type == PIPE_NODE)
		execute_pipe(node, pipe_, exec_index, fd);
	else if (node->type == SIMPLE_CMD)
	{
		if (node->content.simple_cmd.fd_in != ERR && node->content.simple_cmd.fd_out != ERR)
			ft_exec_cmd(node, pipe_, exec_index);
		else
		{
			exit_value_set(1);
			return;
		}
	}
	else if (node->type == OR_NODE)
		execute_or_node(node, pipe_, exec_index);
	else if (node->type == AND_NODE)
		execute_and_node(node, pipe_, exec_index);
	else if (node->type == SEMICO_NODE)
		execute_semicolon_node(node, pipe_, exec_index);
}

void ft_iterate_tree(t_node *node, t_pipe **pipe_, int *exec_index)
{

	if (expansions_perform(node, 0) == true)
	{
		if (execute_redirections(node) == true)
		{
			ft_hanlde_iteration(node, pipe_, exec_index);
		}
		else
			exit_value_set(EXIT_FAILURE);
	}
	else
		exit_value_set(EXIT_FAILURE);
}
