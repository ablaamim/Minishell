/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_char_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:31:54 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/07 10:07:07 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

enum e_char_rules	apply_rules(enum e_char_type char_type)
{
	enum e_char_rules const	apply_rules[] = {
	[NULL_CHAR] = NOT_ACCEPTED,
	[ANY_CHAR] = ACCEPTED,
	[SPACE_CHAR] = NOT_ACCEPTED,
	[SQUOTE_CHAR] = ACCEPTED,
	[DQUOTE_CHAR] = ACCEPTED,
	[LESS_CHAR] = NOT_ACCEPTED,
	[GREAT_CHAR] = NOT_ACCEPTED,
	[AND_CHAR] = NOT_ACCEPTED,
	[SEMICO_CHAR] = NOT_ACCEPTED,
	[PIPE_CHAR] = NOT_ACCEPTED,
	[OP_PARENTH_CHAR] = NOT_ACCEPTED,
	[CLOSE_PARENTH_CHAR] = NOT_ACCEPTED
	};

	return (apply_rules[char_type]);
}

enum e_char_type	define_char_type(char c)
{
	enum e_char_type const	char_type[128] = {
		ANY_CHAR,
	['\t'...'\r'] = SPACE_CHAR,
	[' '] = SPACE_CHAR,
	['\"'] = DQUOTE_CHAR,
	['&'] = AND_CHAR,
	['\''] = SQUOTE_CHAR,
	['('] = OP_PARENTH_CHAR,
	[')'] = CLOSE_PARENTH_CHAR,
	[';'] = SEMICO_CHAR,
	['<'] = LESS_CHAR,
	['>'] = GREAT_CHAR,
	['|'] = PIPE_CHAR
	};

	if (c == '\0')
		return (NULL_CHAR);
	return (char_type[(int) c]);
}
