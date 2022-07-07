/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:05:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/07 21:21:43 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_signal(int signal)
{
	if (signal == SIGINT)
		exit(EXIT_SUCCESS);
}

void	child_sig(int signal)
{
	if (signal == SIGINT)
		printf("\n");
}
