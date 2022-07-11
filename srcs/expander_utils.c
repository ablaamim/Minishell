/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:32:04 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/11 09:24:13 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_array(char ***array)
{
	int	i;

	i = 0;
	while ((*array)[i] != NULL)
	{
		free((*array)[i]);
		++i;
	}
}

int	get_length_without_quotes(char *str)
{
	bool	in_squotes;
	bool	in_dquotes;
	int		i;
	int		len;

	in_squotes = false;
	in_dquotes = false;
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' && in_dquotes == false)
			|| (str[i] == '"' && in_squotes == false))
			change_quote_state(str[i], &in_squotes, &in_dquotes);
		else
			++len;
		++i;
	}
	return (len);
}

void	restore_quotes(char *str)
{
	while (*str != '\0')
	{
		if (*str < 0)
			*str *= -1;
		++str;
	}
}

char	*rm_quotes(char *str)
{
	bool	in_squotes;
	bool	in_dquotes;
	int		i;
	int		j;
	char	*without_quotes;

	in_squotes = false;
	in_dquotes = false;
	i = 0;
	j = 0;
	without_quotes = (char *) malloc(sizeof(*without_quotes)
			* (get_length_without_quotes(str) + 1));
	 if (without_quotes == 0x0)
		 return (0x0);
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' && in_dquotes == false)
			|| (str[i] == '"' && in_squotes == false))
			change_quote_state(str[i], &in_squotes, &in_dquotes);
		else
			without_quotes[j++] = str[i];
		++i;
	}
	restore_quotes(without_quotes);
	return (without_quotes);
}

void	remove_quotes_from_argument(char **arg)
{
	char	*tmp;

	tmp = rm_quotes(*arg);
	free(arg);
	*arg = tmp;
}

