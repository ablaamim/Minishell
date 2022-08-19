/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_performer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:31:06 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/19 21:01:07 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	expander(t_simple_cmd *cmd)
{
	int	i;

	i = 0x0;
	while (cmd->argv[i] != 0x0)
	{
		if (ft_strchr(cmd->argv[i], '$') != 0x0 && !(i > 0x0 && ft_strcmp(cmd->argv[i - 1], "<<") == 0x0))
			if (variable_expansion(cmd, i) == false)
				return (false);
		++i;
	}
	i = 0x0;
	while (cmd->argv[i] != 0x0)
	{
		if (ft_strcmp(cmd->argv[i], "<<") == 0x0)
			cmd->input_has_quotes = (ft_strchr(cmd->argv[i + 1], '\'') != 0x0 || ft_strchr(cmd->argv[i + 1], '"') != 0x0);
		remove_quotes_from_argument(&cmd->argv[i]);
		i++;
	}
	return (true);
}

/*
 * Perform expansions recursively !!
 *
 * $> /bin/echo lol ==> works
 *
 * $> /bin/echo "lol" ==> Does not remove last quote
 *
 * $> /bin/echo "'lol'" ==> leave only one double quote
 * 
 * $> /bin/echo "''lol''" ==> Works
 *
 * [ TO DO ]
 * 
 * -> fixs single and double quotes bugs.
 *
 */

bool	expansions_perform(t_node *ast)
{
	if (ast->type == SIMPLE_CMD)
		return (expander(&ast->content.simple_cmd));
	else
	{
		if (ast->content.child.left != 0x0)
			if (expansions_perform(ast->content.child.left) == false)
				return (false);
		if (ast->content.child.right != 0x0)
			if (expansions_perform(ast->content.child.right) == false)
				return (false);
	}
	return (true);
}
