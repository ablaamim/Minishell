/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_single_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 22:33:59 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/19 22:48:10 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_variable_name_and_val(char *arg, char **var_name, char **var_val)
{
	if ((*arg + 1) == '?')
	{
		printf("====> EXIT STATUS DUH : \n");
		*var_name = ft_strdup("?");
		*var_val = ft_itoa(*retrieve_exit_status());
	}
}

bool	expand_single_variable(t_simple_cmd *cmd, int i, int *j, bool in_dquotes)
{
	char	*var_name;
	char	*var_val;

	(void) in_dquotes;
	get_variable_name_and_val(&cmd->argv[i][*j], &var_name, &var_val);
	return (true);
}
