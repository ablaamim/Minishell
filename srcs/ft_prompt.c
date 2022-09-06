/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 01:03:37 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * the read_line() function reads from input using readline(), saves it in a
 * char * then it returns it to be used in next program.
 * -> Add history.
 * -> Control EOF to exit with ctrl+D.
 */

void	signal_command2(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		exit_value_set(130);
	}
	if (sig == SIGQUIT)
	{
		printf("QUIT\n");
		exit(EXIT_SUCCESS);
	}
}

char	*read_line(void)
{
	char	*line;
	char	*prompt;

	prompt = ft_strdup("");
	signal(SIGINT, signal_command);
	signal(SIGQUIT, SIG_IGN);
	ft_handle_prompt(&prompt);
	line = readline(prompt);
	signal(SIGINT, signal_command2);
	add_history(line);
	if (line == 0x0)
	{
		free(prompt);
		variadic_error_printer(2, "exit\n");
		shell_exit(*retrieve_exit_status(), 0x0);
	}
	free(prompt);
	return (line);
}

/*
 * Signals handling : ctrl+c and ctrl+\
 */

void	signal_command(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		printf("\033[0;32m");
		rl_replace_line("", 0x0);
		rl_redisplay();
		exit_value_set(1);
	}
	if (sig == SIGQUIT)
	{
		printf("QUIT\n");
		exit(EXIT_SUCCESS);
	}
}

void	signal_command_child(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0x0);
	}
	if (sig == SIGQUIT)
	{
		printf("QUIT\n");
		exit(EXIT_SUCCESS);
	}
}

/*
 * Read command input via readline() inside the read_line() program and run
 * another program to continue the work [ft_executor()].
 * -> Also handle signals inside the infinite loop.
 * -> free line.
 */

void	ft_minishell(void)
{
	char	*line;

	while (1337)
	{
		line = read_line();
		ft_executor(line);
		free(line);
	}
}
