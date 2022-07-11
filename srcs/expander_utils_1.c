/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:36:15 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/11 08:15:49 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_quote_state(char quote, bool *in_squotes, bool *in_dquotes)
{
	if (quote == '\'' && *in_dquotes == false)
		*in_squotes = (*in_squotes == false);
	else if (quote == '"' && *in_squotes == false)
		*in_dquotes = (*in_dquotes == false);
}

char	*get_after_var(char *str, int index_dollar)
{
	char	*ptr;

	ptr = str + index_dollar + 1;
	while (ft_isalnum(*ptr) == 1 || *ptr == '_')
		++ptr;
	return (ptr);
}
