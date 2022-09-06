/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:06:07 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/05 23:53:44 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isdigit(int v)
{
	if (v >= 48 && v <= 57)
		return (1);
	else
		return (0);
}

void	ft_handle_cmd(t_node *node, t_pipe **pipe, int *exec_index)
{
	int	pid;
	int	**pipes;

	pipes = NULL;
	pipes = ft_to_array(pipe);
	pid = fork();
	if (pid == ERR)
		shell_exit(EXIT_FAILURE, strerror(errno));
	if (!pid)
	{
		signal(SIGQUIT, SIG_DFL);
		ft_handle_child(node, pipe, *exec_index);
	}
	if (*exec_index == ft_lstsize(*pipe))
	{
		ft_close_pipes(*pipe, pipes);
		ft_handle_parent(node, pid, pipe);
	}
	ft_free_to_array(pipe, pipes);
	(*exec_index)++;
}

int	ft_exec_cmd(t_node *node, t_pipe **pipe, int *exec_index)
{
	int	error;

	error = 0;
	ft_handle_cmd(node, pipe, exec_index);
	if (error)
		return (2);
	else
		return (1);
}

void	ft_free_pipes(t_pipe **pipe)
{
	t_pipe	*p;
	t_pipe	*tmp;

	p = *pipe;
	while (p)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
}

void	ft_handle_reset(t_pipe **pipe, int *exec_index)
{
	ft_free_pipes(pipe);
	*pipe = NULL;
	*exec_index = 0;
}
