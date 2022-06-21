/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:16:51 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/21 17:29:13 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Execute left side of the tree on child process.
*/

void	pipe_child_process_executor(t_node *ast, int file_descriptor[2],\
t_io_streams_file *saver)
{
	printf("ARE YOU OK ???\n\n");
	close(file_descriptor[OUTPUT]);
	dup2(file_descriptor[INPUT], 1);
	close(file_descriptor[INPUT]);
	close(saver->input_stream);
	saver->input_stream = -1;
	close(saver->output_stream);
	saver->output_stream = -1;
	execute_ast_data(ast->content.child.left, true);
	close(1);
	close(0);
	close(2);
	printf("IS THERE ANY PROBLEM HERE ??\n\n");
	exit(EXIT_SUCCESS);
}

/*
 * Execute right side of the ast, also wait child to finish first.
*/

void	pipe_parent_process_executor(t_node *ast, int file_descriptor[2], \
t_io_streams_file *saver)
{
	//GOTTA IGNORE SIGINT [CASE CLOSE]
	signal(SIGINT, SIG_IGN);
	printf("DADDY PROCESS ARE YOU OK ?\n\n");
	close(file_descriptor[INPUT]);
	dup2(file_descriptor[OUTPUT], 0);
	close(file_descriptor[OUTPUT]);
	execute_ast_data(ast->content.child.right, true);
	close(0);
	wait(0x0);
	dup2(saver->input_stream, 0);
	dup2(saver->output_stream, 1);
	close(saver->input_stream);
	saver->input_stream = -1;
	close(saver->output_stream);
	saver->output_stream = -1;
	printf("NANI THE HELL\n\n");

}

void	execute_pipes(t_node *ast)
{
	t_io_streams_file	*saver;
	int					file_descriptor[2];
	pid_t				pid;

	saver = retrieve_io();
	saver->input_stream = dup(0);
	saver->output_stream = dup(1);
	if (pipe(file_descriptor) == -1)
		shell_exit(EXIT_FAILURE, strerror(errno));
	pid = fork();
	if (pid == -1)
		shell_exit(EXIT_FAILURE, strerror(errno));
	/*
	 * TO DO :
	 * Create parent and child functions.
	*/
	if (pid == 0x0)
	{
		pipe_child_process_executor(ast, file_descriptor, saver);
	}
	else
	{
		pipe_parent_process_executor(ast, file_descriptor, saver);
		printf("==============>PARENT FINISHED!!!\n\n");
	}
}
