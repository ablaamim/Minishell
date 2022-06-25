/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:10:38 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/25 01:50:16 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function to free all file descriptors beyond or equal to 3.
*/

void	ft_free_fd(void)
{
	int	fd;

	fd = open("console", O_WRONLY);
	while (fd >= 0)
	{
		if (fd >= 3)
			close(fd);
		break ;
	}
}

/*
 * main() is the Entry point of my program, init and launch all process.
 *
 * ===> if argc == 1 (progam name)
 * - Init env.
 * - Free all filedescriptors beyond or equal to 3.
 * - Init my minishell.
 * ===> Else print ERROR using variadic_error_printer()
*/

int	main(int argc, char **argv, char **env)
{
	if (argc == 1)
	{
		init_bash_env(file_extract(argv[0]), env);
		//printf("============================================================\n\n");
		ft_free_fd();
		ft_minishell();
	}
	else
	{
		if (argv_error_handler(argv[1]))
			return (*retrieve_exit_status());
	}
	return (EXIT_SUCCESS);
}
