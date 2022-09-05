/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:11:38 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/05 20:49:36 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * in simple_cmd there is data that you will need to manage redirections.
 * ->input_stream.
 * ->output_stream.
 * ->boolean value that determines if input stream has single or double quotes
 */

bool parse_redirection(char *argument)
{
	return (ft_strcmp(">", argument) == 0x0 || ft_strcmp(">>", argument) == 0x0 || ft_strcmp("<", argument) == 0x0 ||
			ft_strcmp("<<", argument) == 0x0);
}

t_redirs *redirections_manager(char **args, int *fd_in, int *fd_out,
							   t_node *node)
{
	t_redirs *redir;

	(void)node;
	redir = 0x0;
	if (strcmp("<", *args) == 0x0)
	{
		if (*fd_in != 0)
			close(*fd_in);
		redir = redirection_generator();
		redir->type = INPUT_REDIR;
		redir->file_name = *(args + 1);
	}
	else if (ft_strcmp("<<", *args) == 0x0)
	{
		if (*fd_in != 0)
			close(*fd_in);
		redir = redirection_generator();
		redir->type = HEREDOC_REDIR;
		redir->file_name = *(args + 1);
	}
	else
		redir = redirs_help_manager(args, fd_out, redir);
	return (redir);
}

void clear_redirs_from_input(char **input)
{
	int i;

	i = 2;
	while (input[i] != 0x0)
	{
		input[i - 2] = input[i];
		++i;
	}
	input[i - 2] = input[i];
}

bool open_redir_stream(char **argv, int *fd_in, int *fd_out, t_node *node)
{
	int i;
	t_redirs *redir;

	i = 0x0;
	while (argv[i] != 0x0)
	{
		if (parse_redirection(argv[i]) == true)
		{
			redir = redirections_manager(&argv[i], fd_in, fd_out, node);
			redir_appender(redir, &node->content.simple_cmd.redirs);
			clear_redirs_from_input(&argv[i]);
		}
		else
			++i;
	}
	return (true);
}

bool execute_redirections(t_node *node)
{
	if (node->type == SIMPLE_CMD)
	{
		return (open_redir_stream(node->content.simple_cmd.argv,
								  &node->content.simple_cmd.fd_in,
								  &node->content.simple_cmd.fd_out, node));
	}
	else
	{
		if (node->content.child.left != 0x0)
		{
			if (execute_redirections(node->content.child.left) == false)
				return (false);
		}
		if (node->content.child.right != 0x0)
		{
			if (execute_redirections(node->content.child.right) == false)
				return (false);
		}
		return (true);
	}
}
