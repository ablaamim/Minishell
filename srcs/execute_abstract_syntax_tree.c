/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_abstract_syntax_tree.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:49:57 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 19:31:23 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Execute a simple command in child process, parent must wait.
*/

void	ft_exec_simple_cmd(t_simple_cmd cmd)
{
	pid_t				pid;
	t_io_streams_file	saver;

	saver.input_stream = dup(0);
	saver.output_stream = dup(1);
	dup2(cmd.fd_in, 0);
	dup2(cmd.fd_out, 1);

	if (cmd.argv[0] != 0x0 && cmd.argv[0][0] != 0x0 && \
			builtins_executor(retrieve_len_array(cmd.argv), \
				cmd.argv, saver) == EXIT_COMMAND_NOT_FOUND)
	{
		pid = fork();
		if (pid == -1)
			shell_exit(EXIT_FAILURE, strerror(errno));
		else if (pid == 0)
			exec_in_child(cmd, saver);
		else
			exec_in_parent(pid);
	}
	ft_close_fd(saver);
}

/*
 * Execute a simple command in child process using execve().
 * [BUGGY TOO.] [CASE CLOSED]
 * [TO DO : IMPLEMENT REDIRECTIONS]
 * [CASE CLOSED]
 * [IMPLEMENT EXPANSIONS]
*/

void	ft_complex_exec(t_node *ast, bool pipe)
{
	if (shell_expansions(ast) == true)
	{
		if (execute_redirections(ast) == true)
		{
			if (pipe == false)
			{
				if (retrieve_len_array(ast->content.simple_cmd.argv) == 1\
					&& ast->content.simple_cmd.argv[0][0] == '\0')
					exit_value_set(EXIT_SUCCESS);
				else
				{
					ft_exec_simple_cmd(ast->content.simple_cmd);
				}
			}
			else
				execute_pipes(ast);
		}
		else
			exit_value_set(EXIT_FAILURE);
	}
	else
		exit_value_set(EXIT_FAILURE);
}

/*
 * Core function of my executor.
 * [SURGICAL DEBUGGING ALL OVER!]
 * [CASE CLOSED]
*/

void	execute_ast_data(t_node *ast)
{
	if (ast->type == SIMPLE_CMD)
	{
		printf("================= SIMPLE CMD EXECUTION : ===============\n\n");
		ft_complex_exec(ast, false);
	}
	else if (ast->type == PIPE_NODE)
	{
		ft_pipe_setter(true);
		ft_complex_exec(ast, true);
		ft_pipe_setter(false);
	}
	else
		execute_commands_list(ast);
}
