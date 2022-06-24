/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:53:07 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/24 10:25:56 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reset_term(struct termios	*terminal)
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

/*
 * Initialize terminal.
*/

void	terminal_initialization(int status)
{
	struct termios	terminal;

	if (isatty(STDIN_FILENO))
	{
		if (!tcgetattr(STDIN_FILENO, &terminal))
		{
			reset_term(&terminal);
			if (status)
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
