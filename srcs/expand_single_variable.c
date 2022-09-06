/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_single_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 22:33:59 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 00:01:45 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_len_variable_name(char *argument)
{
	int	len;

	len = 0x0;
	while ((ft_isalnum(argument[len]) != 0x0 || argument[len] == '_') || \
			argument[len] != '\0')
		++len;
	return (len);
}

/*
int	env_val_length(char **val)
{
	int	len;

	len = 0x0;
	while (val[len])
		len++;
	return (len);
}
*/
char	*get_variable_name(char *argument)
{
	char	*var_name;
	int		i;
	int		j;

	i = 1;
	j = 0;
	var_name = garbage_malloc(sizeof(*var_name) * \
			(get_len_variable_name(argument + i) + 1));
	while ((ft_isalnum(argument[i]) != 0x0 || argument[i] == '_') && \
			argument[i] != '\0')
	{
		var_name[j] = argument[i];
		++i;
		++j;
	}
	var_name[j] = '\0';
	return (var_name);
}

char	*quotes_reversal(char *var_value)
{
	char	*str;
	int		i;

	i = 0x0;
	if (var_value == 0x0)
		return (0x0);
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

void	get_variable_name_and_val(char *arg, char **var_name, char **var_val)
{
	if (*(arg + 1) == '?')
	{
		*var_name = ft_strdup("?");
		*var_val = ft_itoa(*retrieve_exit_status());
	}
	else
	{
		*var_name = get_variable_name(arg);
		*var_val = quotes_reversal(get_env(*var_name));
		if (*var_val == 0x0)
			*var_val = "";
	}
}

bool	expand_single_variable(t_simple_cmd *cmd, int const i, int *j, \
		bool in_dquotes)
{
	char	*var_name;
	char	*var_val;

	get_variable_name_and_val(&cmd->argv[i][*j], &var_name, &var_val);
	if (in_dquotes == false && var_val != 0x0 && *var_val != '\0' && \
			has_space(var_val) == true)
	{
		if (ft_reallocate_arg(cmd, i, j, var_val) == false)
		{
			garbage_free((void **)&var_name);
			if (*var_val != '\0')
				garbage_free((void **)&var_val);
			return (false);
		}
	}
	else
	{
		cmd->argv[i] = new_argument(&cmd->argv[i], ft_strlen(var_name), \
				*j, var_val);
		*j += ft_strlen(var_val);
	}
	garbage_free((void **)&var_name);
	if (*var_val != '\0')
		garbage_free((void **)&var_val);
	return (true);
}
