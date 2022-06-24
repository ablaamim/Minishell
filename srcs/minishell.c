/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:10:38 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/24 10:37:21 by ablaamim         ###   ########.fr       */
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
		/*
		 * TO DO :
		 * Init terminal, block display of ctrl+c, ctrl+d ... (^C, ^D ...)
		*/
		terminal_initialization(0x0);
		ignoring_signals(SIGQUIT);
		ignoring_signals(SIGTSTP);
		ignoring_signals(SIGTTIN);
		ignoring_signals(SIGTTOU);
		ignoring_signals(SIGTERM);
		ignoring_signals(SIGHUP);
		/*
		 * Init bash environment.
		*/
		printf("============================================================\n\n");
		//ft_print_env(env);
		/*
		 * Free all fd beyond or equal to 3.
		*/
		ft_free_fd();
		/*
		 * Core funtion.
		*/
		ft_minishell();
	}
	else
	{
		/*
		 * print error using perror() on stderr in case if user enter extra
		 * args.
		*/
		if (argv_error_handler(argv[1]))
			return (*retrieve_exit_status());
	}
	return (EXIT_SUCCESS);
}
