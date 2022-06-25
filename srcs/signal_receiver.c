/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_receiver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:45:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/25 01:22:32 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_receiver(int signal, siginfo_t *infos, void *opt)
{
	(void)	infos;
	(void)	opt;

	if (signal == SIGINT)
	{
		exit_value_set(0x1);
		ft_putendl("");
		rl_on_new_line();
		rl_replace_line("", 0x0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		handling_sigquit(signal);
}
