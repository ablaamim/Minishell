/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_in_stream.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:14:18 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/09 18:14:18 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_len_variable_name(char *arg)
{
	int	len;

	len = 0x0;
	while (ft_isalnum(arg[len]) != 0 || arg[len] != '\0')
		++len;
	return (len);
}

char	*quotes_reverse(char *var_value)
{
	char	*str;
	int		i;

	if (var_value == NULL)
		return (NULL);
	i = 0;
	str = garbage_malloc(sizeof(*str) * (ft_strlen(var_value) + 1));
	while (var_value[i] != '\0')
	{
		if (var_value[i] == '\'' || var_value[i] == '"')
			str[i] = -var_value[i];
		else
			str[i] = var_value[i];
		++i;
	}
	str[i] = '\0';
	return (str);
}

char	*get_variable_name(char *arg)
{
	int		i;
	int		j;
	char	*var_name;

	j = 0;
	i = 1;
	var_name = garbage_malloc(sizeof(*var_name) * (get_len_variable_name(arg + i) + 1));
	while (ft_isalnum(arg[i]) != 0 && arg[i] != '\0')
	{
		var_name[j] = arg[i];
		++i;
		++j;
	}
	var_name[j] = '\0';
	return (var_name);
}

 void	get_variable_name_and_val(char *arg, char **var_name, char **var_value)
{
	if (*(arg + 1) == '?')
	{
		*var_name = ft_strdup("?");
		*var_value = ft_itoa(*retrieve_exit_status());
	}
	else
	{
		*var_name = get_variable_name(arg);
		*var_value = quotes_reverse(get_env(*var_name));
		if (*var_value == NULL)
			*var_value = "";
	}
}

void	expand_vars_in_stream(char **argument)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	while ((*argument)[i] != '\0')
	{
		if ((*argument)[i] == '$')
		{
			
			get_variable_name_and_val(*argument + i, &var_name, &var_value);
			*argument = fill_new_argument(argument, ft_strlen(var_name), i, var_value);
			i += ft_strlen(var_value);
			garbage_free((void **)&var_name);
			if (*var_value != '\0')
				free(var_value);

		}
		else
			++i;
	}
}