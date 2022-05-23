/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:04:00 by ablaamim          #+#    #+#             */
/*   Updated: 2022/05/23 19:02:48 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_cmd(char *buff, int nbuff)
{
	write(0x1, "minishell$>", 11);
	memset(buff, 0x0, nbuff);
	fgets(buff, nbuff, stdin);
	if (buff[0] == 0x0) // EOF
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	static char	buff[256];
	int			fd;
	if (argc == 1)
	{
		fd = open("console", O_RDWR);
		while (fd >= 0)
		{
			if (fd >= 3)
				close(fd);
			break;
		}
		while (get_cmd(buff, sizeof(buff)) >= 0)
		{
			if(buff[0] == 'c' && buff[1] == 'd' && buff[2] == ' ')
			{
				buff[strlen(buff) - 1] = 0;  // chop \n	
				if(chdir(buff + 3) < 0)
					fprintf(stderr, "cannot cd %s\n", buff + 3);
				continue;
			}
		}
	}
	else
	{
		write(2, "Error\n", 6);
	}
	exit(EXIT_SUCCESS);
}
