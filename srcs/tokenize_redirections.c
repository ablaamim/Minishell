/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:55:06 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/09 17:55:04 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
 * Tokenize the LESSER_TOK AND DLESSER_TOKEN.
*/

t_token	*tokenize_lesser(char *in_characters, int *i)
{
	char				*data;
	enum e_token_type	type;

	if (define_char_type(in_characters[++(*i)] == LESS_CHAR))
	{
		data = garbage_malloc(sizeof(*data) * SIZEOF_TWO_CHAR_STRING);
		ft_strlcpy(data, "<<", sizeof(SIZEOF_TWO_CHAR_STRING));
		type = DLESSER_TOKEN;
		++(*i);
	}
	else
	{
		data = garbage_malloc(sizeof(*data) * SIZEOF_ONE_CHAR_STRING);
		ft_strlcpy(data, "<", SIZEOF_ONE_CHAR_STRING);
		type = LESSER_TOKEN;
	}
	return (token_generator(data, type));
}

t_token	*tokenize_greater(char *in_characters, int *i)
{
	char				*data;
	enum e_token_type	type;

	if (define_char_type(in_characters[++(*i)]) == GREAT_CHAR)
	{
		data = garbage_malloc(sizeof(*data) * SIZEOF_TWO_CHAR_STRING);
		ft_strlcpy(data, ">>", SIZEOF_TWO_CHAR_STRING);
		type = DGREATER_TOKEN;
	}
	else
	{
		data = garbage_malloc(sizeof(*data) * SIZEOF_ONE_CHAR_STRING);
		ft_strlcpy(data, ">", SIZEOF_ONE_CHAR_STRING);
		type = GREATER_TOKEN;
	}
	return (token_generator(data, type));
}
