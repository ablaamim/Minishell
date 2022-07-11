/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 11:38:10 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 20:47:00 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	verify_next_character(char c)
{
	return (c == '\0' ||(ft_isalnum(c) == 0  && c != '?'));
}

bool	has_a_space(char *str)
{
	while (*str != '\0')
		if (ft_isspace(*(str++)))
			return (true);
	return (false);
}

void	retrieve_variable_name_and_value(char *argument, char **variable_name, char **variable_value)
{
	if (*(argument + 1) == '?')
	{
		*variable_name = ft_strdup("?");
		*variable_value = ft_itoa(*retrieve_exit_status());
	}
	else
	{
		*variable_name = get_variable_name(argument);
		*variable_name = quotes_reverse(get_env(*variable_name));
		if (variable_value == 0x0)
			*variable_value = "";
	}
}

bool	expand_single_variable(t_simple_cmd *cmd, int i, int *j, bool is_dquotes)
{
	char	*variable_name;
	char	*variable_value;

	retrieve_variable_name_and_value(&cmd->argv[i][*j], &variable_name, &variable_value);
	if (is_dquotes == false && variable_value != 0x0 && *variable_value != '\0' && has_a_space(variable_value) == true)
	{
		if (reallocate_argument(cmd, i, j, variable_value) == false)
		{
			free(variable_name);
			if (variable_value != '\0')
				free(variable_value);
			return (false);
		}
	}
	else
	{
		cmd->argv[i]
			= fill_new_argument(&cmd->argv[i], ft_strlen(variable_name), *j, variable_value);
		*j += ft_strlen(variable_value);
	}
	free(variable_name);
	if (*variable_value != '\0')
		free(variable_value);
	return (true);
}

bool	variables_expansion(t_simple_cmd *cmd, int i)
{
	int		j;
	bool	is_squoted;
	bool	is_dquoted;

	is_squoted = false;
	is_dquoted = false;
	j = 0x0;
	while (cmd->argv[i] != 0x0 &&  cmd->argv[i][j] != '\0')
	{
		if (cmd->argv[i][j] == '$' && is_squoted == false)
		{
			if (verify_next_character(cmd->argv[i][j + 1]) == true)
				cmd->argv[i] = fill_new_argument(&cmd->argv[i], 0x0, j++, "$");
			else
				if (expand_single_variable(cmd, i, &j, is_dquoted) == false)
					return (false);
		}
		else
		{
			change_quote_state(cmd->argv[i][j], &is_squoted, &is_dquoted);
			++j;
		}
	}
	return (true);
}
