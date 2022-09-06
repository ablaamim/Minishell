/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:14:09 by gruz              #+#    #+#             */
/*   Updated: 2022/09/06 20:09:49 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_empty_or_nodes(t_node *node, t_pipe **pipe_,
		int *exec_index, int *heredoc)
{
	if (node->type == OR_NODE)
	{
		if (node->content.child.left)
			ft_init_heredoc(node->content.child.left,
				pipe_, exec_index, heredoc);
		if (*heredoc == 2)
			*heredoc = 1;
		if (node->content.child.right)
			ft_init_heredoc(node->content.child.right,
				pipe_, exec_index, heredoc);
	}
	else if (node != NULL)
	{
		if (node->content.child.left)
			ft_init_heredoc(node->content.child.left,
				pipe_, exec_index, heredoc);
		if (node->content.child.right)
			ft_init_heredoc(node->content.child.right,
				pipe_, exec_index, heredoc);
	}
}

void	ft_handle_execution(t_node *ast)
{
	int		exec_init;
	int		heredoc;
	t_pipe	*pipe;

	exec_init = 0;
	pipe = NULL;
	heredoc = 0;
	ft_init_heredoc(ast, &pipe, &exec_init, &heredoc);
	if (heredoc == 1)
		return ;
	heredoc = 1;
	exec_init = 1;
	ft_init_heredoc(ast, &pipe, &exec_init, &heredoc);
	exec_init = 0;
	ft_iterate_tree(ast, &pipe, &exec_init);
	ft_free_pipes(&pipe);
	ast_clearing(&ast);
}

void	ft_handle_dup2(t_node *node, t_pipe **pipe, int **pipes, int exec_index)
{
	if (node->content.simple_cmd.fd_in == 0)
	{
		if (exec_index - 1 >= 0)
			dup2(pipes[exec_index - 1][0], 0);
	}
	else
		dup2(node->content.simple_cmd.fd_in, 0);
	if (node->content.simple_cmd.fd_out == 1)
	{
		if (exec_index < ft_lstsize(*pipe))
			dup2(pipes[exec_index][1], 1);
	}
	else
		dup2(node->content.simple_cmd.fd_out, 1);
}
