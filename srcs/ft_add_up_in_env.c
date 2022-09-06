/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_up_in_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:18:07 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 20:16:28 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_add_up_in_env(const char *name, const char *val, t_env env)
{
	int		i;
	t_env	new_env;

	i = 0x0;
	new_env = garbage_malloc(sizeof(char *) * (env_length(env) + 2));
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	if (val == 0x0)
		new_env[i++] = ft_strjoin(name, val, "");
	else
		new_env[i++] = ft_strjoin(name, val, "=");
	new_env[i] = NULL;
	return (new_env);
}

int	ft_handle_line(char *line, t_redirs *redirs, t_node *node)
{
	line = readline(">");
	if (line == 0x0)
	{
		free(line);
		return (0x0);
	}
	if (!ft_strcmp(line, redirs->file_name))
	{
		free(line);
		return (0);
	}
	heredoc_expander(&line);
	write(node->content.simple_cmd.fd_in, line, ft_strlen(line));
	write(node->content.simple_cmd.fd_in, "\n", 1);
	free(line);
	return (1);
}

void	ft_handle_heredoc_child(char *line, t_redirs *redirs,
	t_node *node, char *tmp)
{
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		if (ft_handle_line(line, redirs, node) == 0)
			break ;
	}
	free(line);
	line = ft_strjoin(tmp, redirs->file_name, "");
	close(node->content.simple_cmd.fd_in);
	free(tmp);
	exit_value_set(0);
	exit(0);
}

void	ft_handle_heredoc(t_redirs *redirs, t_node *node, int *heredoc)
{
	char	*line;
	char	*tmp;
	int		pid;

	tmp = ft_strdup("/tmp/");
	line = ft_strjoin(tmp, redirs->file_name, "");
	node->content.simple_cmd.fd_in = open(line,
			O_RDWR | O_TRUNC | O_CREAT, 0777);
	pid = fork();
	if (!pid)
	{
		ft_handle_heredoc_child(line, redirs, node, tmp);
	}
	while (wait(NULL) > 0)
		write(2, "", 0);
	close(node->content.simple_cmd.fd_in);
	node->content.simple_cmd.fd_in = open(line, O_RDONLY);
	free(line);
	free(tmp);
	if (*retrieve_exit_status() == 130)
		*heredoc = 1;
}

void	ft_handle_redirections(t_redirs *redirs, t_node *node,
	int *heredoc, int init_heredoc)
{
	if (redirs == NULL)
		return ;
	else if (redirs->type == INPUT_REDIR && !init_heredoc)
	{
		ft_hanlde_input_redir(node, heredoc, redirs);
	}
	else if (redirs->type == OUTPUT_REDIR
		&& !init_heredoc)
	{
		ft_handle_output_redir(node, heredoc, redirs);
	}
	else if (redirs->type == APPEND_OUTPUT_REDIR && !init_heredoc)
	{
		ft_handle_append_redir(node, redirs, heredoc);
	}
	else if (redirs->type == HEREDOC_REDIR && init_heredoc)
		ft_handle_heredoc(redirs, node, heredoc);
	ft_handle_redirections(redirs->next, node, heredoc, init_heredoc);
}
