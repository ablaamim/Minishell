/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocument_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:04:10 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/07 22:47:23 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_intput_heredoc(char **doc, char *line)
{
	char	*tmp;

	tmp = *doc;
	if (tmp == 0x0)
		*doc = ft_strdup(line);
	else
		*doc = ft_strjoin(tmp, line, "\n");
	free(tmp);
	free(line);
}

bool	heredocument_control(char const *delimiter, char *line)
{
	if (line == 0x0 && ft_strcmp(delimiter, "") == 0x0)
		return (true);
	else if (line != 0x0)
	{
		if (ft_strcmp(line, delimiter) == 0x0)
			return (true);
		return (false);
	}
	return (false);
}

char	*here_document(char const *delimiter)
{
	char	*line;
	char	*doc;

	doc = 0x0;
	while (1337)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &heredoc_signal);
		line = readline("heredoc> ");
		//if (sigint_catcher(doc, line) == true)
		//	return (0x0);
		//signal(SIGQUIT, SIG_IGN);
		//signal(SIGINT, heredoc_signal);
		printf("\n");
		if (heredocument_control(delimiter, line) == true)
			break;
		append_intput_heredoc(&doc, line);
	}
	free(line);
	append_intput_heredoc(&doc, 0x0);
	return (doc);
}

int	heredoc_redir(char const *stream, bool input_had_quotes)
{
	char	*doc;
	int		fd[2];
	int		pid;

	pid = fork();
	signal(SIGINT, &child_sig);
	signal(SIGQUIT, &child_sig);
	if (pid == 0x0)
	{
		doc = here_document(stream);
		if (doc == 0x0)
		{
			exit_value_set(130);
			return (-1);
		}
		free(doc);
	}
	waitpid(pid, retrieve_exit_status(), 0x0);
	//if (input_had_quotes == false && doc != 0x0)
	/*
	 * TO DO :  HERE-DOC explansion
	*/
	input_had_quotes = true;
	if (input_had_quotes == true && doc != 0x0)
		printf("HANDLE EXPANSIONS DUUUDE !\n");

	if (pipe(fd) == -1)
		shell_exit(EXIT_FAILURE, strerror(errno));
	if (doc != 0x0)
		ft_putstr_fd(doc, fd[0]);
	close(fd[0]);
	return (fd[1]);
}
