/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:14:05 by gruz              #+#    #+#             */
/*   Updated: 2022/09/06 20:15:34 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

void	ft_hanlde_input_redir(t_node *node, int *heredoc, t_redirs *redirs)
{
	node->content.simple_cmd.fd_in = open(redirs->file_name, O_RDONLY);
	if (node->content.simple_cmd.fd_in == ERR)
	{
		variadic_error_printer(2, "minishell: %s : %s\n",
			strerror(errno), redirs->file_name);
		*heredoc = 2;
		exit_value_set(1);
		return ;
	}
}

void	ft_handle_output_redir(t_node *node, int*heredoc, t_redirs *redirs)
{
	node->content.simple_cmd.fd_out
		= open(redirs->file_name, O_RDWR | O_TRUNC | O_CREAT, 0777);
	{
		if (node->content.simple_cmd.fd_out == ERR)
		{
			variadic_error_printer(2, "minishell: %s : %s\n",
				strerror(errno), redirs->file_name);
			*heredoc = 2;
			exit_value_set(1);
			return ;
		}
	}
}

void	ft_handle_append_redir(t_node *node, t_redirs *redirs, int *heredoc)
{
	node->content.simple_cmd.fd_out
		= open(redirs->file_name, O_RDWR | O_APPEND | O_CREAT, 0777);
	if (node->content.simple_cmd.fd_out == ERR)
	{
		variadic_error_printer(2, "minishell: %s : %s\n",
			strerror(errno), redirs->file_name);
		*heredoc = 2;
		exit_value_set(1);
		return ;
	}
}
