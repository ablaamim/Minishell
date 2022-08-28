/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:59:08 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/28 11:13:20 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Add the new_token to the linked list.
*/

void	append_token(t_token *new_token, t_token **token_list)
{
	t_token	*current;

	if (*token_list == 0x0)
		*token_list = new_token;
	else
	{
		current = *token_list;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}
