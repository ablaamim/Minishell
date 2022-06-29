/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 01:21:09 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/29 01:21:13 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_reset_terminal(struct termios *terminal)
{
	terminal->c_lflag &= ~terminal->c_lflag;
	terminal->c_lflag |= (ISIG | ICANON | IEXTEN | ECHO | NOFLSH);
	terminal->c_iflag &= ~terminal->c_iflag;
	terminal->c_iflag |= (ICRNL | IXON | IXANY | IMAXBEL | IUTF8);
	terminal->c_oflag &= ~terminal->c_oflag;
	terminal->c_oflag |= (OPOST | ONLCR);
	terminal->c_cflag &= ~terminal->c_cflag;
	terminal->c_cflag |= (CREAD | CS8);
}

void	ft_init_terminal(int state)
{
	struct termios	terminal;

	if (isatty(STDIN_FILENO))
	{
		if (!tcgetattr(STDIN_FILENO, &terminal))
		{
			ft_reset_term(&terminal);
			if (state)
				terminal.c_lflag |= (ECHOCTL);
			if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal))
			{
				perror("tcsetattr");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			perror("tcgetattr");
			exit(EXIT_FAILURE);
		}
	}
}
