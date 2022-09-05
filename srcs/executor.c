/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/05 21:25:28 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void env_setter(char *name, char *val, int replace, t_env *env);

// void ft_iterate_tree(t_node *node, t_pipe **pipe_, int *exec_index)
// {
// 	int fd[2];

// 	if (expansions_perform(node, 1) == true)
// 	{
// 		if (execute_redirections(node) == true)
// 		{
// 			if (node->type == PIPE_NODE)
// 			{
// 				if (pipe(fd) == ERR)
// 					shell_exit(EXIT_FAILURE, strerror(errno));
// 				ft_lstadd_front(pipe_, ft_lstnew(fd));
// 				ft_iterate_tree(node->content.child.left, pipe_, exec_index);
// 				ft_iterate_tree(node->content.child.right, pipe_, exec_index);
// 			}
// 			else if (node->type == SIMPLE_CMD)
// 			{
// 				if (node->content.simple_cmd.fd_in != ERR && node->content.simple_cmd.fd_out != ERR)
// 					ft_exec_cmd(node, pipe_, exec_index);
// 				else
// 				{
// 					exit_value_set(1);
// 					return;
// 				}
// 			}
// 			else if (node->type == OR_NODE)
// 			{
// 				ft_iterate_tree(node->content.child.left, pipe_, exec_index);
// 				ft_handle_reset(pipe_, exec_index);
// 				if (*retrieve_exit_status() != 0)
// 					ft_iterate_tree(node->content.child.right, pipe_, exec_index);
// 			}
// 			else if (node->type == AND_NODE)
// 			{
// 				execute_and_node(node, pipe_, exec_index);
// 			}
// 			else if (node->type == SEMICO_NODE)
// 			{
// 				if (node->content.child.left)
// 					ft_iterate_tree(node->content.child.left, pipe_, exec_index);
// 				ft_handle_reset(pipe_, exec_index);
// 				if (node->content.child.right)
// 					ft_iterate_tree(node->content.child.right, pipe_, exec_index);
// 			}
// 		}
// 		else
// 			exit_value_set(EXIT_FAILURE);
// 	}
// 	else
// 		exit_value_set(EXIT_FAILURE);
// }

void ft_handle_init_heredoc(t_node *node, t_pipe **pipe_, int *exec_index, int *heredoc)
{
	if (node->type == SIMPLE_CMD)
	{
		if (*heredoc)
			ft_handle_redirections(node->content.simple_cmd.redirs, node, heredoc, 0);
		else
			ft_handle_redirections(node->content.simple_cmd.redirs, node, heredoc, 1);
	}
	else if (node->type == OR_NODE)
	{
		if (node->content.child.left)
			ft_init_heredoc(node->content.child.left, pipe_, exec_index, heredoc);
		if (*heredoc == 2)
			*heredoc = 1;
		if (node->content.child.right)
			ft_init_heredoc(node->content.child.right, pipe_, exec_index, heredoc);
	}
	else if (node != NULL)
	{
		if (node->content.child.left)
			ft_init_heredoc(node->content.child.left, pipe_, exec_index, heredoc);
		if (node->content.child.right)
			ft_init_heredoc(node->content.child.right, pipe_, exec_index, heredoc);
	}
}

void ft_init_heredoc(t_node *node, t_pipe **pipe_, int *exec_index, int *heredoc)
{
	if (expansions_perform(node, 0) == true)
	{
		if (execute_redirections(node) == true)
			ft_handle_init_heredoc(node, pipe_, exec_index, heredoc);
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
				heredoc = 1;
				ft_init_heredoc(ast, &pipe, &exec_init, &heredoc);
				ft_iterate_tree(ast, &pipe, &exec_init);
				ft_free_pipes(&pipe);
				ast_clearing(&ast);
			}
		}
	}
}
