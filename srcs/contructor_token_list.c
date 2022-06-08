/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contructor_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:48:08 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/08 17:50:07 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Util function to espace all whitespaces.
*/

bool	ft_iswhite_space(int c)
{
	if (c == 32 || (c >= 7 && c <= 14))
		return (true);
	else
		return (false);
}

/*
int	main(void)
{
	char	str[] = "lel haha   \tESCAPE ME            \n";
	int	i = 0x0;
	printf("%s\n", str);
	while (str[i])
	{
		if (ft_iswhite_space(str[i]))
			str[i] = '-';
		i++;
	}
	printf("%s\n", str);
}
*/

/*
 * This particular constructor will build the tokens linked list based on
 * the read buffer from readline() respecting LEXER grammar, 
 * first of all, i must escape all the white spaces, 
 * until the in_characters [string] is fully scanned, i will
 * operate couple of algorithms, i must retrieve next token, using the
 * retrieve_next_token() function, this token will be added to the tokens
 * linked list by append_token() function, after that i must escape
 * whitespaces again
*/

bool	constructor_token_list(char *in_characters, t_token **token_list)
{
	t_token	*next_token;
	int		i;

	i = 0x0;
	while (ft_iswhite_space(in_characters[i]))
		++i;
	while (in_characters[i])
	{
		//printf("NB OF SKIPPED WHITESPACES IN BEGENING : %d\n", i);
		while (ft_iswhite_space(in_characters[i]))
			++i;
	}
	return (true);
}
