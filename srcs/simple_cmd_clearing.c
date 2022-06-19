/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_clearing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:37:02 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/19 16:40:16 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	simple_cmd_clearing(t_node **simple_cmd)
{
	int	i;

	i = 0x0;
	if (*simple_cmd != 0x0)
	{
		i = 0x0;
		while ((*simple_cmd)->content.simple_cmd.argv[i] != 0x0)
		{
			free((*simple_cmd)->content.simple_cmd.argv[i]);
			++i;
		}
		free((*simple_cmd)->content.simple_cmd.argv);
		free(*simple_cmd);
	}
}
