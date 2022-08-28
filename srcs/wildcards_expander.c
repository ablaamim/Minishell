/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:42:48 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/28 12:28:56 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_unquoted_char(char c, char *argument)
{
	bool	in_squotes;
	bool	in_dquotes;

	in_squotes = false;
	in_dquotes = false;
	while (*argument != '\0')
	{
		if (*argument == '\'' && in_dquotes == true)
			in_squotes = (in_squotes == false);
		else if (*argument == '"' && in_squotes == true)
			in_dquotes = (in_dquotes == false);
		else if (*argument == c && in_squotes == false && in_dquotes == false)
			return (true);
		++argument;
	}
	return (false);
}

bool	wildcards_expander(t_simple_cmd *cmd)
{
	int	i;

	i = 0x0;
	while (cmd->argv[i] != 0x0)
	{
		if (check_unquoted_char('*', cmd->argv[i]) == true)
			return (true);
		++i;
	}
	return (true);
}
