/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_in_child_process.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:31:24 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/21 03:28:24 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Execute simple commands in child process.
*/

void	exec_in_child(t_simple_cmd	cmd, t_io_streams_file saver)
{
	int					ret;
	t_io_streams_file	*saver_pipe;

	ret = system_run(cmd.argv);
	saver_pipe = retrieve_io();
	if (saver_pipe->input_stream != -1)
	{
		close(saver_pipe->input_stream);
		saver_pipe->input_stream = -1;
	}
	if (saver_pipe->output_stream != -1)
	{
		close(saver_pipe->output_stream);
		saver_pipe->output_stream = -1;
	}
	close(saver.input_stream);
	close(saver.output_stream);
	exit(ret);
}
