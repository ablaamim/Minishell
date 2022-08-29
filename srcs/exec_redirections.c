/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:11:38 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/29 12:50:26 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * in simple_cmd there is data that you will need to manage redirections.
 * ->input_stream.
 * ->output_stream.
 * ->boolean value that determines if input stream has single or double quotes
 */

bool	parse_redirection(char *argument)
{
	return (ft_strcmp(">", argument) == 0x0 || ft_strcmp(">>", \
				argument) == 0x0 || ft_strcmp("<", argument) == 0x0 || \
			ft_strcmp("<<", argument) == 0x0);
}

t_redirs	*redirection_generator(void)
{
	t_redirs	*new_redir;

	new_redir = garbage_malloc(sizeof(*new_redir));
	new_redir->fd[0] = 0x0;
	new_redir->fd[1] = 0x1;
	new_redir->type = 0x0;
	new_redir->file_name = 0x0;
	new_redir->next = 0x0;
	return (new_redir);
}

void	redir_appender(t_redirs *new_redir, t_redirs **lst_redir)
{
	t_redirs	*current;

	if (*lst_redir == 0x0)
		*lst_redir = new_redir;
	else
	{
		current = *lst_redir;
		while (current->next)
			current = current->next;
		current->next = new_redir;
		new_redir->next = NULL;
	}
}

void	print_redir_list(t_redirs *redir)
{
	t_redirs	*current;

	current = redir;
	if (current == 0x0)
		printf("THERE IS NO REDIR IN CMD\n");
	while (current)
	{
		if (current->type == INPUT_REDIR)
			printf("TYPE = INPUT REDIR | ");
		else if (current->type == OUTPUT_REDIR)
			printf("TYPE = OUTPUT REDIR | ");
		else if (current->type == HEREDOC_REDIR)
			printf("TYPE = HEREDOC REDIR | ");
		else
			printf("TYPE = APPEND REDIR | ");
		printf("FILE NAME = %s |", current->file_name);
		if (current->next == 0x0)
			printf("-->NULL\n");
		current = current->next;
	}
}

t_redirs	*redirections_manager(char **args, int *fd_in, int *fd_out, \
		t_node *node)
{
	t_redirs	*redir;

	(void)node;
	redir = 0x0;
	if (strcmp("<", *args) == 0x0)
	{
		redir = redirection_generator();
		if (*fd_in != 0)
			close(*fd_in);
		redir->type = INPUT_REDIR;
		redir->file_name = *(args + 1);
	}
	else if (ft_strcmp("<<", *args) == 0x0)
	{
		if (*fd_in != 0)
			close(*fd_in);
		redir->type = HEREDOC_REDIR;
		redir->file_name = *(args + 1);
	}
	else if (ft_strcmp(">", *args) == 0x0)
	{
		if (*fd_out != 1)
			close(*fd_out);
		redir = redirection_generator();
		redir->type = OUTPUT_REDIR;
		redir->file_name = *(args + 1);
	}
	else if (ft_strcmp(">>", *args) == 0x0)
	{
		if (*fd_out != 1)
			close(*fd_out);
		redir = redirection_generator();
		redir->type = APPEND_OUTPUT_REDIR;
		redir->file_name = *(args + 1);
	}
	return (redir);
}

void	clear_redirs_from_input(char **input)
{
	int	i;

	i = 2;
	while (input[i] != 0x0)
	{
		input[i - 2] = input[i];
		++i;
	}
	input[i - 2] = input[i];
}

bool	open_redir_stream(char **argv, int *fd_in, int *fd_out, t_node *node)
{
	int			i;
	t_redirs	*redir;

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

bool	execute_redirections(t_node *node)
{
	if (node->type == SIMPLE_CMD)
	{
		return (open_redir_stream(node->content.simple_cmd.argv, \
					&node->content.simple_cmd.fd_in, \
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
