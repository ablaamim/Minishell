/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignoring_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:29:23 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/24 10:38:21 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void	ignoring_signals(int signal)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0x0;
	sigemptyset(&(sa.sa_mask));
	sigaddset(&(sa.sa_mask), signal);
	if (sigaction(signal, &sa, 0x0))
	{
		perror(strerror(signal));
		exit (EXIT_FAILURE);
	}
}
