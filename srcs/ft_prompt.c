/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/02 12:43:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * the read_line() function reads from input using readline(), saves it in a
 * char * then it returns it to be used in next program.
 * -> Add history.
 * -> Control EOF to exit with ctrl+D.
 */

void	ft_handle_prompt(char **line)
{
	char	*tmp;
	char	*data;
	char	*data_tmp;
	int		i;

	data_tmp = getenv("PWD");
	tmp = getenv("HOME");
	//printf("==> HOME = %s\n", tmp); //HOME ENV VAR
	//printf("==> PWD = %s\n", data_tmp); // PWD ENV VAR
	i = 0;
	printf("\033[0;32m");
	while (data_tmp[i] && data_tmp[i] == tmp[i])
		i++;
	if (ft_strlen(tmp) > ft_strlen(data_tmp))
		i = 0;
	else
		data_tmp = ft_strjoin("~", data_tmp + i, "");
	data = ft_strjoin(getenv("USER"), getenv("NAME"), "@");
	tmp = ft_strjoin(data, data_tmp, "\033[0;37m:\033[0;36m");
	free(data);
	data = ft_strjoin(tmp, "\033[0;37m$ ", "");
	*line = ft_strdup(data);
	free(tmp);
	free(data);
}

char	*read_line(void)
{
	char	*line;
	char	*prompt;

	prompt = ft_strdup("");
	ft_handle_prompt(&prompt);
	line = readline(prompt);
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
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0x0);
		rl_redisplay();
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

void	ft_minishell(t_env *env)
{
	char	*line;

	//ft_print_env(*env);
	while (1337)
	{
		line = read_line();
		signal(SIGINT, signal_command);
		signal(SIGQUIT, SIG_IGN);
		ft_executor(line, env);
		free(line);
	}
}
