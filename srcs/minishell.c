/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:10:38 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/07 12:04:17 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function to free all file descriptors beyond 2
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

int	main(int argc, char **argv, char **env)
{
	bool	inline_mode;

	if (argc == 1)
	{
		//ft_print_env(env);
		ft_free_fd();
		ft_prompt(inline_mode);
	}
	else
	{
		write(2, ARGV_ERROR, sizeof(ARGV_ERROR));
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
