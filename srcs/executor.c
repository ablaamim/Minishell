/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 17:48:21 by gruz             ###   ########.fr       */
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
	else if (node->type == OR_NODE)
	{
		if (node->content.child.left)
			ft_init_heredoc(node->content.child.left,
				pipe_, exec_index, heredoc);
		if (*heredoc == 2)
			*heredoc = 1;
		if (node->content.child.right)
			ft_init_heredoc(node->content.child.right,
				pipe_, exec_index, heredoc);
	}
	else if (node != NULL)
	{
		if (node->content.child.left)
			ft_init_heredoc(node->content.child.left,
				pipe_, exec_index, heredoc);
		if (node->content.child.right)
			ft_init_heredoc(node->content.child.right,
				pipe_, exec_index, heredoc);
	}
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
	t_pipe	*pipe;
	int		exec_init;
	int		heredoc;

	heredoc = 0;
	ast = 0x0;
	pipe = NULL;
	exec_init = 0;
	if (line != 0x0)
	{
		ast = ft_lexer_parser_program(line);
		{
			if (ast != 0x0)
			{
				ft_init_heredoc(ast, &pipe, &exec_init, &heredoc);
				if (heredoc == 1)
					return ;
				heredoc = 1;
				exec_init = 1;
				ft_init_heredoc(ast, &pipe, &exec_init, &heredoc);
				exec_init = 0;
				ft_iterate_tree(ast, &pipe, &exec_init);
				ft_free_pipes(&pipe);
				ast_clearing(&ast);
			}
		}
	}
}
