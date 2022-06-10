/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_identifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:15:36 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/10 17:50:18 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * returns true if the token is either "&&", "||" or ";", else false.
*/

bool	check_logical_operators(enum e_token_type	type)
{
	return (type == SEMICO_TOKEN || type == OR_TOKEN || type == AND_TOKEN);
}

/*
 * returns true of the token is an opening or a closing parenthesis, otherwise
 * return false.
*/

bool	identify_parenthesis(enum e_token_type	type)
{
	return (type == OP_PARENTH_TOKEN || type == CLOSE_PARENTH_TOKEN);
}

/*
 * returns trueif the token redirection, otherwise return false.
*/

bool	identify_redirection(enum e_token_type	type)
{
	return (type == LESSER_TOKEN || type == DLESSER_TOKEN || type == \
			GREATER_TOKEN || type == DGREATER_TOKEN);
}

/*
 * Returns true if the token is a part of a simple command, otherwise returns
 * false.
*/

bool	identify_leaf(enum e_token_type	type)
{
	return (identify_redirection(type) == true || type == WORD_TOKEN);
}
