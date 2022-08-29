/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:20:17 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/29 13:45:30 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redirs	*redirs_help_manager(char **args, int *fd_out, t_redirs *redir)
{
	if (ft_strcmp(">", *args) == 0x0)
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
