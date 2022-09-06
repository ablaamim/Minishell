/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_from_argument.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:50:53 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 22:29:46 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	substitute_quotes_state(char quote, bool *in_squotes, bool *in_dquotes)
{
	if (quote == '\'' && *in_dquotes == false)
		*in_squotes = (*in_squotes == false);
	else if (quote == '"' && *in_squotes == false)
		*in_dquotes = (*in_dquotes == false);
}

static int	calculate_len_without_quotes(char *str)
{
	bool	in_dquotes;
	bool	in_squotes;
	int		i;
	int		len;

	i = 0x0;
	len = 0x0;
	in_dquotes = false;
	in_squotes = false;
	while (str[i] != 0x0)
	{
		if ((str[i] == '\'' && in_dquotes == false) || \
				(str[i] == '"' && in_squotes == false))
			substitute_quotes_state(str[i], &in_squotes, &in_dquotes);
		else
			++len;
		++i;
	}
	return (len);
}

void	quotes_restore(char *str)
{
	while (*str != 0x0)
	{
		if (*str < 0x0)
			*str *= -1;
		++str;
	}
}

/*
 * Remove quotes from arguments in order to perform expansions.
 *
 * BUGS ENCOUTRED : i remove only one quote (squote / dquote) lol !!!
 *
 * -> if input has no quotes it works like a charm !
 *  i will fix it later
 *
 *  [CASE SOLVED !]
 *
 */

static char	*remove_quotes(char *str)
{
	bool	in_dquotes;
	bool	in_squotes;
	int		i;
	int		j;
	char	*without_quotes;

	in_dquotes = false;
	in_squotes = false;
	i = 0x0;
	j = 0x0;
	without_quotes = garbage_malloc(sizeof(*without_quotes) * \
			(calculate_len_without_quotes(str) + 0x1));
	while (str[i] != 0x0)
	{
		if ((str[i] == '\'' && in_dquotes == false) || (str[i] == '"' && \
					in_squotes == false))
			substitute_quotes_state(str[i], &in_squotes, &in_dquotes);
		else
			without_quotes[j++] = str[i];
		++i;
	}
	quotes_restore(without_quotes);
	return (without_quotes);
}

void	remove_quotes_from_argument(char **argv)
{
	char	*tmp;

	tmp = remove_quotes(*argv);
	garbage_free((void **)argv);
	*argv = tmp;
}
