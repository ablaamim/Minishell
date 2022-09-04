/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:54:22 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/04 21:30:26 by gruz             ###   ########.fr       */
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

char *retrieve_var_val(char *str, char *env_val)
{
	char *var_val;

	if (*(str - 2) == '+')
		var_val = ft_strdup(env_val);
	else
		var_val = ft_strdup(str);
	return (var_val);
}

int special_env_len(t_env *env)
{
	int len = 0x0;
	while ((*env)[len])
		len++;
	return (len);
}

