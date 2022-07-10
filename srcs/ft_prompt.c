/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 17:29:03 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * the read_line() function reads from input using readline(), saves it in a 
 * char * then it returns it to be used in next program.
 * ---> Add history.
 * ---> Control EOF to exit with ctrl+D.
*/

char	*read_line(void)
{
	char	*line;

	line = readline("minishell-v1.0$> ");
	add_history(line);
	if (line == 0x0)
	{
		variadic_error_printer(2, "exit\n");
		shell_exit(*retrieve_exit_status(), 0x0);
	}
	return (line);
}

/*
 * Signals handling.
*/

void	signal_command(int sig)
{
	printf("\n\n==> sig value : %d\n\n", sig);
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0x0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		variadic_error_printer(2, "Quit\n");
		exit(EXIT_FAILURE);
	}
}

/*
 * Read command input via readline() inside the read_line() program and run
 * another program to continue the work [ft_executor()].
 * --> Also handle signals inside the infinite loop.
*/

void	ft_minishell(void)
{
	char	*line;

	while (1337)
	{
		line = read_line();
		signal(SIGINT, signal_command);
		signal(SIGQUIT, signal_command);
		ft_executor(line);
		free(line);
	}
}
