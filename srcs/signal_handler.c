/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:57:19 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/25 01:21:23 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handling_sigquit(int signal)
{
	char	**env;
	char	*nb_cmd;

	(void)signal;
	env = env_reader(ENV_FILE);
	if (!env)
		return ;
	nb_cmd = get_env_array("?nb_cmd", env);
	if (!ft_strcmp(nb_cmd, "1"))
		ft_putendl_fd("Quit: 3", 2);
	free(nb_cmd);
	free_chararray(env);
}

void	handling_sigint(int signal, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;
	(void)signal;
	ft_putendl("");
}

void	toggle_signals(int toggle)
{
	if (toggle)
	{
		wait_for_signals(SIGINT, handling_sigint);
		wait_for_signals(SIGQUIT, signal_receiver);
	}
	else
	{
		wait_for_signals(SIGINT, signal_receiver);
		ignoring_signals(SIGQUIT);
	}
	terminal_initialization(toggle);
}

