/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:28:59 by ablaamim          #+#    #+#             */
/*   Updated: 2022/05/24 19:34:05 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close_file_descriptors(void)
{
	int	fd;

	fd = open("console", O_RDWR);
	while (fd >= 0)
	{
		if (fd >= 3)
			close(fd);
		break ;
	}
}

int	main(int argc, char **argv)
{
	(void) argv;
	if (argc == 1)
	{
		ft_close_file_descriptors();
		ft_prompt();
	}
	else
	{
		write(2, ERROR_MSG_ARG, sizeof("ERROR_MSG_ARG"));
	}
	return (EXIT_SUCCESS);
}
