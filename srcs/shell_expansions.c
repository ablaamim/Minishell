/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:46:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/21 21:57:11 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	expander(t_simple_cmd *cmd)
{
	int	i;

	i = 0x0;
	while (cmd->argv[i] != 0x0)
	{
		if (ft_strchr(cmd->argv[i], '$') != 0x0)
		/*
		 * TO DO :
		 * perform variable expansion.
		*/
			//if (variables_expansion(cmd, i) == false)
				return (false);
		++i;
	}
	while (cmd->argv[i] != 0x0)
	{
		++i;
	}
	return (true);
}

bool	shell_expansions(t_node *ast)
{
	if (ast->type == SIMPLE_CMD)
		return (expander(&ast->content.simple_cmd));
	return (true);
}
