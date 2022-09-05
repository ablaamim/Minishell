/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:11:17 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/04 14:53:27 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * ft_free_fd() : this function will free all file descriptors beyond 3.
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
 * main() : is the Entry point of my program, init and launch all process.
 *
 * -> if argc == 1 (progam name)
 * - Init environment.
 * - Signal handling [SIGINT = ctrl+c / SIGQUIT = ctrl+\ / EOF = ctrl+d].
 * - Free all filedescriptors beyond or equal to 3.
 * - Init my minishell [Core function].
 * - free all filedescriptors beyond 3 again.
 *
 * -> Else print ERROR using variadic_error_printer()
 *  and return 127 because if we execute this test we need an exit value of 127
 *
 * $> ./minishell ARGUMENT
 *
 * $> echo $?
 *
 * $> 127
 *
*/

/*
 * init_bash_env() : function to clone the cache of host bash and save it
 * in accessible memory, like this we will have a copy of bash environment.
*/

int	main(int argc, char **argv, char  **env)
{
	(void) argv;

	if (argc == 1)
	{
		init_bash_env(argv[0], env);
		ft_free_fd();
		ft_minishell();
	}
	else
	{
		variadic_error_printer(2, "Error : Feature not supported\n");
		return (127);
	}
	return (EXIT_SUCCESS);
}
