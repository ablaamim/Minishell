/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:28:35 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/19 21:50:32 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * EXPAND VARIABLES :
 *
 * [TO DO]
 * -> Expand variable.
*/

bool	variable_expansion(t_simple_cmd *cmd, int i)
{
	int		j;
	bool	in_squotes;
	bool	in_dquotes;

	j = 0x0;
	in_squotes = false;
	in_dquotes = false;
	while (cmd->argv[i][j] != 0x0 && cmd->argv[i][j] != '\0')
	{
		if (cmd->argv[i][j] == '$' && in_squotes == false)
		{
			printf("EXPAND THIS SHIT\n\n");
			break;
		}
		else
		{
			substitute_quotes_state(cmd->argv[i][j], &in_squotes, &in_dquotes);
			++j;
		}
	}
	return (true);
}
