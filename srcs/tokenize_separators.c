/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_separators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:53:41 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/07 10:09:02 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Tokenize the opening parentheses amd the closing parentheses
*/

t_token	*tokenize_parentheses(char *in_characters, int *i)
{
	char				*data;
	enum e_token_type	type;

	if (in_characters[*i] == '(')
		type = OP_PARENTH_TOKEN;
	else
		type = CLOSE_PARENTH_TOKEN;
	data = garbage_malloc(sizeof (*data) * SIZEOF_ONE_CHAR_STRING);
	ft_strlcpy(data, &in_characters[*i], SIZEOF_ONE_CHAR_STRING);
	++(*i);
	return (token_generator(data, type));
}

/*
 * Tokenize the semicolon token
*/

t_token	*tokenize_semicolon(char *in_characters, int *i)
{
	char				*data;

	(void) in_characters;
	data = garbage_malloc(sizeof(*data) * SIZEOF_ONE_CHAR_STRING);
	ft_strlcpy(data, ";", SIZEOF_ONE_CHAR_STRING);
	++(*i);
	return (token_generator(data, SEMICO_TOKEN));
}

/*
 * Tokenize the AND_TOKEN And the AMPERSAND_TOKEN, the AMPERSAND_TOKEN is
 * not handled by my program, if it is found i display error on stderr.
*/

t_token	*tokenize_and(char *in_characters, int *i)
{
	enum e_token_type	type;
	char				*data;

	if (define_char_type(in_characters[++(*i)]) == AND_CHAR)
	{
		data = garbage_malloc(sizeof(*data) * SIZEOF_TWO_CHAR_STRING);
		ft_strlcpy(data, "&&", SIZEOF_TWO_CHAR_STRING);
		type = AND_TOKEN;
		++(*i);
	}
	else
	{
		variadic_error_printer(2, "This feature is not suppoted\n");
		return (0x0);
	}
	return (token_generator(data, type));
}

/*
 * Tokenize the PIPE_TOKEN and the OR_TOKEN at the same time
*/

t_token	*tokenize_pipe(char *in_characters, int *i)
{
	enum e_token_type	type;
	char				*data;

	if (define_char_type(in_characters[++(*i)]) == PIPE_CHAR)
	{
		data = garbage_malloc(sizeof(*data) * SIZEOF_TWO_CHAR_STRING);
		ft_strlcpy(data, "||", SIZEOF_TWO_CHAR_STRING);
		type = OR_TOKEN;
		++(*i);
	}
	else
	{
		data = garbage_malloc(sizeof(*data) * SIZEOF_ONE_CHAR_STRING);
		ft_strlcpy(data, "|", SIZEOF_ONE_CHAR_STRING);
		type = PIPE_TOKEN;
	}
	return (token_generator(data, type));
}
