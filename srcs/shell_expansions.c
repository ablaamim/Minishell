/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:46:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/11 09:54:06 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	expander(t_simple_cmd *cmd)
{
	int	i;

	i = 0x0;
	while (cmd->argv[i] != 0x0)
	{
		if (ft_strchr(cmd->argv[i], '$') != 0x0 && !(i > 0x0 && ft_strcmp(cmd->argv[i - 1], "<<") == 0x0))
			//if (variables_expansion(cmd, i) == false)
				//return (false);
				return (true);
		++i;
	}
	/*
	if (wild_card_expansion(cmd) == false)
		return (false);
	*/
	/*
	i = 0x0;
	while (cmd->argv[i] != 0x0)
	{
		if (ft_strcmp(cmd->argv[i], "<<") == 0x0)
			cmd->input_has_quotes = (ft_strchr(cmd->argv[i + 1],  '\'') != 0x0\
					|| ft_strchr(cmd->argv[i + 1], '"') != 0x0);
			remove_quotes_from_argument(&cmd->argv[i]);
		++i;
	}
	*/
	return (true);
}

bool	shell_expansions(t_node *ast)
{
	if (ast->type == SIMPLE_CMD)
		return (expander(&ast->content.simple_cmd));
	else
	{
		if (ast->content.child.left != 0x0)
			if (shell_expansions(ast->content.child.left) == false)
				return (false);
		if (ast->content.child.right != 0x0)
			if (shell_expansions(ast->content.child.right) == false)
				return (false);
	}
	return (true);
}
