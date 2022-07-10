/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:05:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 09:24:56 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_signal(int signal)
{
	if (signal == SIGINT)
		exit(EXIT_FAILURE);
}

void	child_sig(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n\nCHILD CONTROL\n\n");
		exit(EXIT_FAILURE);
	}
}
