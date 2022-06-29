/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/29 15:36:10 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

/*
 * read_line function reads from input using readline, saves it in a char *
 * then it returns it to be used in next program.
 * -> Control eof to exit.
*/

char	*read_line(void)
{
	char	*line;

	line = readline("Minishell$>");
	if (line == 0x0)
	{
		variadic_error_printer(2, "exit\n");
		exit(EXIT_SUCCESS);
	}
	return (line);
}

void	signal_command(int sig)
{
	g_exit_status += sig;
	//printf("%d\n", sig);
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0x0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		variadic_error_printer(2, "Quit (Core dumped)\n");
		exit(EXIT_FAILURE);
	}
}

/*
 * Read command input via readline() inside the read_line program and runs
 * another program to continue the work
*/

void	ft_minishell(void)
{
	char	*line;

	while (true)
	{
		line = read_line();
		signal(SIGINT, signal_command);
		signal(SIGQUIT, SIG_IGN);
		ft_executor(line);
	}
}
