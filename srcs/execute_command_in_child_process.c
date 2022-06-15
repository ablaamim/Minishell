/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_in_child_process.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:31:24 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/15 18:39:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Execute simple commands in child process.
*/

void	exec_in_child(t_simple_cmd	cmd)
{
	int	ret;

	ret = system_run(cmd.argv);
	exit(ret);
}
