/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_one_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:21:52 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/04 23:11:22 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

#define ERROR_MINISHELL "error : exit minishell\n"

/*
 * Function to print content of env
*/

void	ft_print_envp(char **env)
{
	int	param;

	param = 0x0;
	while (env[param])
	{
		printf("%s\n", env[param]);
		param++;
	}
}

/*
 * read input from stdin and return a line
*/

char	*read_line(bool inline_mode)
{
	char	*line;

	line = NULL;
	if (inline_mode == false)
	{
		line = readline("minishell$>");
		if (!line)
			return (NULL);
		add_history(line);
	}
}

/*
 * Mandatory function : read command line using readline(),
 * and execute it
*/

void	minishell(bool inline_mode)
{
	char	*line;

	while (true)
	{
		line = read_line(inline_mode);
	}
}

/*
 * Init minishell && launch all processes
*/

int	main(int argc, char **argv, char **env)
{
	bool	inline_mode;

	if (argc == 1)
	{
		//ft_print_envp(env);
		minishell(inline_mode);
	}
	else
	{
		write(2, ERROR_MINISHELL, sizeof(ERROR_MINISHELL));
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
