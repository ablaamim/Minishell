/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_clearing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:52:47 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/19 16:55:07 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokens_clearing(t_token **token_list)
{
	t_token	*previous;
	t_token	*current;

	if (*token_list == 0x0)
		return ;
	current = *token_list;
	while (current)
	{
		free(current->data);
		previous = current;
		current = current->next;
		free(previous);
	}
	*token_list = 0x0;
}
