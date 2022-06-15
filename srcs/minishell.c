/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:10:38 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/15 19:22:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function to free all file descriptors beyond 2.
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
 * Verify if its inline_mode.
*/

bool	initialize_term(void)
{
	if (isatty(1) == 0)
		return (true);
	return(false);
}

/*
 * Entry point of my program.
*/

int	main(int argc, char **argv, char **env)
{
	bool	inline_mode;

	if (argc == 1)
	{
		inline_mode = initialize_term();
		//ft_print_env(env);
		ft_free_fd();
		ft_minishell(inline_mode);
	}
	else
	{
		write(2, ARGV_ERROR, sizeof(ARGV_ERROR));
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
