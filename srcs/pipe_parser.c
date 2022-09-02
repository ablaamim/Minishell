/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:49:58 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/03 00:24:22 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Check errors.
*/

bool	check_errors(t_token *token_list)
{
	if (token_list == 0x0)
	{
		variadic_error_printer(2, ERROR_MINISHELL_EOF);
		return (false);
	}
	if (token_list->type == OP_PARENTH_TOKEN)
		return (false);
	return (true);
}

/*
 * A pipe is made of at least one simple command, of a pipe is found after
 * a first command, pipe_parser() will go in a loop following all next steps,
 * untill the next command found is not a pipe.
 * -> the pipe token should be devoured.
 * -> if the list of tokens is empty, i return false.
 * -> the pipe command is allocated and initialized.
 * -> the ast is transfered to the left part of the pipe_node and the 
 *  simple_command_parser() method is called on the right child of the 
 *  pipe_node, if success i return true boolean value.
*/

bool	pipe_parser(t_token **token_list, t_node **ast,bool is_subshell)
{
	t_node	*pipe_node;
	t_node	*simple_command;

	if (simple_command_parser(token_list, &simple_command, \
				is_subshell) == false)
		return (false);
	*ast = simple_command;
	while (*token_list != NULL && (*token_list)->type == PIPE_TOKEN)
	{
		token_devour(token_list);
		if (check_errors(*token_list) == false)
			return (false);
		pipe_node = 0x0;
		pipe_node = garbage_malloc(sizeof(*pipe_node));
		ft_bzero(pipe_node, sizeof(*pipe_node));
		pipe_node->type = PIPE_NODE;
		pipe_node->content.child.left = *ast;
		*ast = pipe_node;
		if (simple_command_parser(
				token_list, &((*ast)->content.child.right), is_subshell) == \
				false)
			return (false);
	}
	return (true);
}
