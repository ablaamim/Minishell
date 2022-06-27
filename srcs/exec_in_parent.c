/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:05:43 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/27 16:19:38 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_in_parent(int pid)
{
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, 0x0, WUNTRACED | WCONTINUED);
}
