/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/04 13:17:53 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * the read_line() function reads from input using readline(), saves it in a
 * char * then it returns it to be used in next program.
 * -> Add history.
 * -> Control EOF to exit with ctrl+D.
 */

char *get_var(char *var_name)
{
	t_env env;
	char *tmp;
	int i;
	int j;

	env = *get_bash_env();
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		tmp = ft_strdup(env[i]);
		tmp[j] = '\0';
		if (!ft_strcmp(tmp, var_name))
			return (env[i] + (j + 1));
		free(tmp);
		i++;
	}
	return (NULL);
}

void ft_handle_prompt(char **line)
{
	char *tmp;
	char *data;
	char *data_tmp;
	int i;

	data_tmp = get_var("PWD");
	tmp = get_var("HOME");
	i = 0;
	printf("\033[0;32m");
	while (data_tmp[i] && data_tmp[i] == tmp[i])
		i++;
	if (ft_strlen(tmp) > ft_strlen(data_tmp))
		i = 0;
	else
		data_tmp = ft_strjoin("~", data_tmp + i, "");
	data = ft_strjoin(get_var("USER"), get_var("NAME"), "@");
	tmp = ft_strjoin(data, data_tmp, "\033[0;37m:\033[0;36m");
	free(data);
	data = ft_strjoin(tmp, "\033[0;37m$ ", "");
	free(*line);
	*line = ft_strdup(data);
	free(tmp);
	free(data);
}

void signal_command2(int sig)
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

char *read_line(void)
{
	char *line;
	char *prompt;

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

void signal_command(int sig)
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

void signal_command_child(int sig)
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

void ft_minishell(void)
{
	char *line;

	// ft_print_env(*env);
	while (1337)
	{
		line = read_line();
		// signal(SIGQUIT, signal_command2);
		ft_executor(line);
		free(line);
	}
}
