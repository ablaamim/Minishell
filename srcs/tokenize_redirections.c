/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:55:06 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/07 19:47:29 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Tokenize the LESSER_TOKEN AND DLESSER_TOKEN.
*/

/*
bool	ft_srch(char *inchars, char c)
{
	int	iter;

	iter = 0x0;
	while (inchars[iter])
	{
		if (inchars[iter] == c)
			if (inchars[iter + 0x1] == c)
				return (true);
		iter++;
	}
	return (false);
}
*/

t_token	*tokenize_lesser(char *in_characters, int *i)
{
	char				*data;
	enum e_token_type	type;

	//printf("\n\n==> ITERATOR VALUE : %d\n", *i);
	//printf("\n\n==> READ LINE : %s\n\n", in_characters);
	if (define_char_type(in_characters[++(*i)]) == LESS_CHAR)
	{
		//printf("ALLO\n\n\n\n");
		//data = (char *) malloc(sizeof(*data) * 3);
		//if (!data)
		//	return (0x0);
		data = garbage_malloc(sizeof(data) * 3);
		ft_strlcpy(data, "<<", 3);
		//ft_memcpy(data, "<<\0", 3);
		type = DLESSER_TOKEN;
		++(*i);
		//printf("\n\n==> data : %s\n\n", data);
		//printf("\n\n===> HEREDOC %s\n\n", data);
	}
	else
	{
		//data = (char *) malloc(sizeof(*data) * 2);
		//if (!data)
		//	return (0x0);
		data = garbage_malloc(sizeof(data) * 2);
		ft_strlcpy(data, "<", 2);
		//ft_memcpy(data, "<\0", 2);
		type = LESSER_TOKEN;
		//printf("\n\n===> INPUT REDIR : %s\n\n", data);
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
		++(*i);
	}
	else
	{
		data = garbage_malloc(sizeof(*data) * SIZEOF_ONE_CHAR_STRING);
		ft_strlcpy(data, ">", SIZEOF_ONE_CHAR_STRING);
		type = GREATER_TOKEN;
	}
	return (token_generator(data, type));
}
