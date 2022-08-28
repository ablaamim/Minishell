/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:54:22 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/28 12:01:43 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*retrieve_after_variable(char *str, int dollar_index)
{
	char	*ptr;

	ptr = str + dollar_index + 1;
	while (ft_isalnum(*ptr) == 1)
		++ptr;
	return (ptr);
}

void	manage_first_join(char *arg, char **new_argv, char \
		**splitted_variable, t_expander *utils)
{
	char	*before_dollar;

	before_dollar = ft_strndup(arg, utils->dollar_index);
	if (utils->first_joined == true)
	{
		new_argv[utils->i_new] = ft_strjoin(before_dollar, \
				splitted_variable[utils->i_split], "");
		++utils->i_new;
		++utils->i_split;
		garbage_free((void **) &before_dollar);
	}
	else if (*before_dollar != '\0')
	{
		new_argv[utils->i_new] = before_dollar;
		++utils->i_new;
	}
	else
		garbage_free((void **) &before_dollar);
}

void	manage_last_join(char *arg, char **new_argv, \
		char **splitted_variable, t_expander *utils)
{
	char	*after_variable;

	after_variable = retrieve_after_variable(arg, utils->dollar_index);
	if (utils->last_joined == true && *after_variable != '\0')
	{
		garbage_free((void **) &new_argv[utils->i_new - 1]);
		new_argv[utils->i_new - 1] = ft_strjoin(\
				splitted_variable[utils->i_split - 1], after_variable, "");
		++utils->i_split;
	}
	else if (*after_variable != '\0')
		new_argv[utils->i_new++] = ft_strdup(after_variable);
}
