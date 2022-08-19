/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/18 23:22:52 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * the read_line() function reads from input using readline(), saves it in a
 * char * then it returns it to be used in next program.
 * -> Add history.
 * -> Control EOF to exit with ctrl+D.
 */

char *read_line(void)
{
	char *line;

	line = readline("Mini Hell-v2.0$> ");
	add_history(line);
	if (line == 0x0)
	{
		variadic_error_printer(2, "exit\n");
		shell_exit(*retrieve_exit_status(), 0x0);
	}
	return (line);
}

/*
 * Signals handling : ctrl+c and ctrl+\
 */

void signal_command(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0x0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		variadic_error_printer(2, "Quit : 3\n");
		exit(EXIT_SUCCESS);
	}
}

/*
 * Read command input via readline() inside the read_line() program and run
 * another program to continue the work [ft_executor()].
 * -> Also handle signals inside the infinite loop.
 * -> free line.
 */

void ft_minishell(char **env)
{
	char *line;

	while (1337)
	{
		line = read_line();
		signal(SIGINT, signal_command);
		signal(SIGQUIT, SIG_IGN);
		ft_executor(line, env);
		free(line);
	}
}
