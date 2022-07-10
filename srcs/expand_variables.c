/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 11:38:10 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 12:11:05 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		// [ TO BE CONTINUED].
		/*
		if (reallocate_argument(cmd, i, j, variable_value) == false)
		{
			free(variable_name);
			if (variable_value != '\0')
				free(variable_value);
			return (false);
		}
		*/
	}
	return (true);
}

bool	variables_expansion(t_simple_cmd *cmd, int i)
{
	int		j;
	bool	is_squoted;
	bool	is_dquotes;

	is_squoted = false;
	is_dquotes = false;
	j = 0x0;
	while (cmd->argv[i] != 0x0 &&  cmd->argv[i][j] != '\0')
	{
		if (cmd->argv[i][j] == '$' && is_squoted == false)
		{
			if (verify_next_character(cmd->argv[i][j + 1]) == true)
				cmd->argv[i] = fill_new_argument(&cmd->argv[i], 0x0, j++, "$");
			else
				if (expand_single_variable(cmd, i, &j, is_dquotes) == false)
					return (false);
		}
	}
	return (true);
}
