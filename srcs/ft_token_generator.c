/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_generator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:10:36 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/09 15:33:11 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Create a new token filled with type and allocated data.
*/

t_token	*token_generator(char *data, enum e_token_type type)
{
	t_token	*new_token;

	new_token = garbage_malloc(sizeof(*new_token));
	new_token->data = data;
	new_token->type = type;
	new_token->next = 0x0;
	ft_print_token(new_token);
	return (new_token);
}
