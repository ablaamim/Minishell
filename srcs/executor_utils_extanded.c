/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_extanded.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:35:58 by gruz              #+#    #+#             */
/*   Updated: 2022/09/06 20:36:22 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_parent_extanded(int pid, int *status, int *gab)
{
	while (waitpid(pid, status, 0x0) > 0)
	{
		while (waitpid(-1, gab, 0x0) > 0)
			;
		if (WIFEXITED(*status))
		{
			exit_value_set(WEXITSTATUS(*status));
			if (WEXITSTATUS(*status) == 17)
				exit_value_set(0x0);
		}
		if (WIFSIGNALED(*status))
			exit_value_set(WTERMSIG(*status) + 128);
	}
}

void	ft_handle_parent(t_node *node, int pid, t_pipe **pipe)
{
	int	status;
	int	gab;

	signal(SIGINT, SIG_IGN);
	if (pid)
	{
		ft_handle_parent_extanded(pid, &status, &gab);
	}
	if (node->content.simple_cmd.argv[0] == 0x0)
		return ;
	status = *retrieve_exit_status();
	if (ft_lstsize(*pipe) == 0
		&& (!ft_strcmp(node->content.simple_cmd.argv[0], "exit")
			|| !ft_strcmp(node->content.simple_cmd.argv[0], "cd")
			|| !ft_strcmp(node->content.simple_cmd.argv[0], "export")
			|| !ft_strcmp(node->content.simple_cmd.argv[0], "unset")
			|| !ft_strcmp(node->content.simple_cmd.argv[0], "echo")))
	{
		status = ft_handle_built_ins(node->content.simple_cmd.argv, node);
		exit_value_set(status);
	}
}
