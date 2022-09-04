/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/04 21:36:20 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void env_setter(char *name, char *val, int replace, t_env *env);

void ft_iterate_tree(t_node *node, t_pipe **pipe_, int *exec_index)
{
	int fd[2];

	if (expansions_perform(node, 1) == true)
	{
		if (execute_redirections(node) == true)
		{
			if (node->type == PIPE_NODE)
			{
				if (pipe(fd) == ERR)
					shell_exit(EXIT_FAILURE, strerror(errno));
				ft_lstadd_front(pipe_, ft_lstnew(fd));
				ft_iterate_tree(node->content.child.left, pipe_, exec_index);
				ft_iterate_tree(node->content.child.right, pipe_, exec_index);
			}
			else if (node->type == SIMPLE_CMD)
				ft_exec_cmd(node, pipe_, exec_index);
			else if (node->type == OR_NODE)
			{
				ft_iterate_tree(node->content.child.left, pipe_, exec_index);
				ft_handle_reset(pipe_, exec_index);
				if (*retrieve_exit_status() != 0)
					ft_iterate_tree(node->content.child.right, pipe_, exec_index);
			}
			else if (node->type == AND_NODE)
			{
				ft_iterate_tree(node->content.child.left, pipe_, exec_index);
				ft_handle_reset(pipe_, exec_index);
				if (*retrieve_exit_status() == 0)
					ft_iterate_tree(node->content.child.right, pipe_, exec_index);
			}
			else if (node->type == SEMICO_NODE)
			{
				ft_iterate_tree(node->content.child.left, pipe_, exec_index);
				ft_handle_reset(pipe_, exec_index);
				ft_iterate_tree(node->content.child.right, pipe_, exec_index);
			}
		}
		else
			exit_value_set(EXIT_FAILURE);
	}
	else
		exit_value_set(EXIT_FAILURE);
}

void ft_init_heredoc(t_node *node, t_pipe **pipe_, int *exec_index, int *heredoc)
{
	if (expansions_perform(node, 0) == true)
	{
		if (execute_redirections(node) == true)
		{
			if (node->type == SIMPLE_CMD)
				ft_handle_redirections(node->content.simple_cmd.redirs, node, heredoc);
			else if (node != NULL)
			{
				ft_init_heredoc(node->content.child.left, pipe_, exec_index, heredoc);
				ft_init_heredoc(node->content.child.right, pipe_, exec_index, heredoc);
			}
		}
		else
			exit_value_set(EXIT_FAILURE);
	}
	else
		exit_value_set(EXIT_FAILURE);
}

void ft_executor(char *line)
{
	t_node *ast;
	t_pipe *pipe;
	int exec_init;
	int heredoc;

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
				if (heredoc == 1) // handle heredoc ctrl + c
					return;
				ft_iterate_tree(ast, &pipe, &exec_init);
				ft_free_pipes(&pipe);
				ast_clearing(&ast);
			}
		}
	}
}
