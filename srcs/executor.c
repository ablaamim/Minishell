/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 18:29:50 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_init_heredoc(t_node *node, t_pipe **pipe_,
	int *exec_index, int *heredoc)
{
	if (node->type == SIMPLE_CMD)
	{
		if (*heredoc)
			ft_handle_redirections(node->content.simple_cmd.redirs,
				node, heredoc, 0);
		else
			ft_handle_redirections(node->content.simple_cmd.redirs,
				node, heredoc, 1);
	}
	else
		ft_empty_or_nodes(node, pipe_, exec_index, heredoc);
}

void	ft_init_heredoc(t_node *node, t_pipe **pipe_,
		int *exec_index, int *heredoc)
{
	int	expand;

	expand = 0;
	if (!*exec_index)
		expand = 1;
	if (expansions_perform(node, expand) == true)
	{
		if (execute_redirections(node) == true)
			ft_handle_init_heredoc(node, pipe_, exec_index, heredoc);
		else
			exit_value_set(EXIT_FAILURE);
	}
	else
		exit_value_set(EXIT_FAILURE);
}

void	ft_executor(char *line)
{
	t_node	*ast;

	ast = 0x0;
	if (line != 0x0)
	{
		ast = ft_lexer_parser_program(line);
		{
			if (ast != 0x0)
			{
				ft_handle_execution(ast);
			}
		}
	}
}
