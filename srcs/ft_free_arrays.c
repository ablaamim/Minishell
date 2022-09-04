/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:21:49 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/04 22:46:41 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_arrays(char **arrays)
{
	int	i;

	i = 0x0;
	while (arrays[i])
	{
		free(arrays[i++]);
	}
	free(arrays);
}

void ft_handle_child_init(t_node *node, t_pipe **pipe, int exec_index)
{
	int **pipes;

	if (node->content.simple_cmd.argv[0] && ft_is_child_ignored(node->content.simple_cmd.argv[0]) && ft_lstsize(*pipe) == 0)
		exit(0);
	pipes = ft_to_array(pipe);
	ft_handle_wildcard(node);
	ft_handle_dup2(node, pipe, pipes, exec_index);
	ft_close_pipes(*pipe, pipes);
	ft_free_to_array(pipe, pipes);
}

void ft_handle_child_execution(t_node *node)
{
	char *bin_path;
	char **argv;
	int ret;
	t_env *env;

	env = get_bash_env();
	if (ft_is_built_in(node->content.simple_cmd.argv[0]))
	{
		ret = ft_handle_built_ins(node->content.simple_cmd.argv, node);
		exit(ret);
	}
	ret = *retrieve_exit_status();
	exit_value_set(ret);
	argv = node->content.simple_cmd.argv;
	if (!argv[0])
		exit(1);
	bin_path = found_binary(argv);
	ret = manage_execution(&bin_path, node->content.simple_cmd.argv[0]);
	if (ret != EXIT_SUCCESS)
	{
		exit_value_set(ret);
		exit(ret);
	}
	if (execve(bin_path, argv, *env) == ERR)
		ret = manage_execution(&bin_path, node->content.simple_cmd.argv[0]);
	garbage_free((void **)&bin_path);
	exit(ret);
}

void ft_handle_child(t_node *node, t_pipe **pipe, int exec_index)
{
	ft_handle_child_init(node, pipe, exec_index);
	ft_handle_child_execution(node);
}


void ft_handle_parent(t_node *node, int pid, t_pipe **pipe)
{
	int status;
	int gab;

	if (pid)
	while (waitpid(pid, &status, 0x0) > 0)
	{
		while (waitpid(-1, &gab, 0x0) > 0)
				;
		if (WIFEXITED(status))
		{
			exit_value_set(WEXITSTATUS(status));
			if (WEXITSTATUS(status) == 17)
				exit_value_set(0x0);
		}
	}
	if (node->content.simple_cmd.argv[0] == 0x0)
		return;
	status = *retrieve_exit_status();
	if (ft_lstsize(*pipe) == 0 && (!ft_strcmp(node->content.simple_cmd.argv[0], "exit") || !ft_strcmp(node->content.simple_cmd.argv[0], "cd") || !ft_strcmp(node->content.simple_cmd.argv[0], "export") ||
								   !ft_strcmp(node->content.simple_cmd.argv[0], "unset") || !ft_strcmp(node->content.simple_cmd.argv[0], "echo")))
	{
		status = ft_handle_built_ins(node->content.simple_cmd.argv, node);
		exit_value_set(status);
	}
}
