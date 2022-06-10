/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_identifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:15:36 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/10 11:37:55 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * returns true if the token is either "&&", "||" or ";", else false.
*/

bool	check_logical_operators(enum e_token_type type)
{
	return (type == SEMICO_TOKEN || type == OR_TOKEN || type == AND_TOKEN);
}
