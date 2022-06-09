/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contructor_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:48:08 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/09 16:47:13 by ablaamim         ###   ########.fr       */
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
 * check for validity of the characters in in_characters string and
 * call apply_rules() function accordingly to the quoting state.
*/

enum e_char_rules	verifier(char c, bool *s_quotes_found, \
		bool *d_quotes_found)
{
	enum e_char_type	char_type;

	char_type = define_char_type(c);
	if (*s_quotes_found == false && *d_quotes_found == false)
	{
		if (char_type == SQUOTE_CHAR)
			*s_quotes_found = true;
		else if (char_type == DQUOTE_CHAR)
			*d_quotes_found = true;
	}
	else
	{
		if (char_type == NULL_CHAR)
			return (NOT_ACCEPTED);
		if (char_type == SQUOTE_CHAR && *s_quotes_found == true)
			*s_quotes_found = false;
		else if (char_type == DQUOTE_CHAR && *d_quotes_found == true)
			*d_quotes_found = false;
		return (ACCEPTED);
	}
	return (apply_rules(char_type));
}

/*
 * starting from the behening occurence of the token in the in_characters
 * string, the validity of every single character us checked inside the
 * verifier() function, if the character is not valid the end of the token is
 * reached, and the function ft_strndup() will add the word identifier to the
 * data field inside the token linked list. squotes and dquotesare verified 
 * as well in the verifier() algorithm.
*/

t_token	*tokenize_word(char *in_characters, int *i)
{
	char	*data;
	int		j;
	bool	s_quotes_found;
	bool	d_quotes_found;

	j = 0x0;
	s_quotes_found = false;
	d_quotes_found = false;
	data = garbage_malloc(sizeof(*data));
	*data = '\0';
	while (verifier(in_characters[*i + j], &s_quotes_found, \
				&d_quotes_found) == ACCEPTED)
		++j;
	if (in_characters[*i + j] == '\0'\
			&& (s_quotes_found == true || d_quotes_found == true))
	{
		write(2, ERROR_MINISHELL_EOF, sizeof(ERROR_MINISHELL_EOF));
		garbage_free((void **) &data);
		return (NULL);
	}
	data = ft_strndup(in_characters + *i, j);
	*i += j;
	return (token_generator(data, WORD_TOKEN));
}

/*
 * function pointer array / dispatch table, this function is called from
 * the parent function retrieve_next_token(), it applies the proper tokenizer
 * depending on the e_char_type encountred along in in_characters string.
*/

t_token	*retrieve_next_token(char	*in_characters, int *i)
{
	t_token	*(*tokenizer[NB_CHAR_TYPE])(char *, int *i);

	tokenizer[NULL_CHAR] = NULL;
	tokenizer[ANY_CHAR] = &tokenize_word;
	tokenizer[SPACE_CHAR] = NULL;
	tokenizer[SQUOTE_CHAR] = &tokenize_word;
	tokenizer[DQUOTE_CHAR] = &tokenize_word;
	return (tokenizer[define_char_type(in_characters[*i])](in_characters, i));
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
	t_token	*new_token;
	int		i;

	i = 0x0;
	while (ft_iswhite_space(in_characters[i]))
		++i;
	while (in_characters[i])
	{
		new_token = retrieve_next_token(in_characters, &i);
		if (new_token == 0x0)
			return (false);
		append_token(new_token, token_list);
		//printf("NB OF SKIPPED WHITESPACES IN BEGENING : %d\n", i);
		while (ft_iswhite_space(in_characters[i]))
			++i;
	}
	return (true);
}
