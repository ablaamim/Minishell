/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_performer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:31:06 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/29 12:47:36 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool expander(t_simple_cmd *cmd, int remove_quotes)
{
	int i;

	i = 0x0;
	while (cmd->argv[i] != 0x0)
	{
		if (ft_strchr(cmd->argv[i], '$') != 0x0 && !(i > 0x0 &&
													 ft_strcmp(cmd->argv[i - 1], "<<") == 0x0))
		{
			if (variable_expansion(cmd, i) == false)
				return (false);
		}
		++i;
	}
	if (!remove_quotes)
		return (true);
	i = 0x0;
	while (cmd->argv[i] != 0x0)
	{
		if (ft_strcmp(cmd->argv[i], "<<") == 0x0)
			cmd->input_has_quotes = (ft_strchr(cmd->argv[i + 1], '\'') != 0x0 || ft_strchr(cmd->argv[i + 1], '"') != 0x0);
		remove_quotes_from_argument(&cmd->argv[i]);
		++i;
	}
	return (true);
}

/*
 * Perform expansions recursively !!
 */

bool expansions_perform(t_node *ast, int remove_quotes)
{
	if (ast->type == SIMPLE_CMD)
		return (expander(&ast->content.simple_cmd, remove_quotes));
	else
	{
		if (ast->content.child.left != 0x0)
		{
			if (expansions_perform(ast->content.child.left, remove_quotes) == false)
				return (false);
		}
		if (ast->content.child.right != 0x0)
		{
			if (expansions_perform(ast->content.child.right, remove_quotes) == false)
				return (false);
		}
	}
	return (true);
}
