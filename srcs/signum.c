/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:00:41 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/29 18:14:56 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int signal)
{
	set_signumber(signal);
	exit_value_set(130);
}

void	handle_signals(void)
{
	signal(SIGTRAP, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGBUS, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
	signal(SIGINT, sigint_handler);
}

int	*retrieve_signumber(void)
{
	static int	signumber = 0x0;

	return (&signumber);
}

void	set_signumber(int signal)
{
	int	*signumber;

	signumber = retrieve_signumber();
	*signumber = signal;

}
