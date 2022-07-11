/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:29:54 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/11 08:28:42 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*allocate_new_argument(char *argument, int len_variable_name, char *variable_value)
{
	char	*new_arg;
	int		len_variable_value;

	len_variable_value = ft_strlen(variable_value);
	new_arg = (char *) malloc(sizeof(*new_arg) * (ft_strlen(argument) \
				- len_variable_name + len_variable_value));
	if (new_arg == 0x0)
		return (0x0);
	return (new_arg);
}

char	*fill_new_argument(char **arg, int len_var_name, int i, char *var_value)
{
	int		j;
	int		k;
	char	*new_arg;

	j = 0;
	new_arg = allocate_new_argument(*arg, len_var_name, var_value);
	while (j < i)
	{
		new_arg[j] = (*arg)[j];
		++j;
	}
	k = 0;
	while (var_value[k])
		new_arg[j++] = var_value[k++];
	i = i + len_var_name + 1;
	while ((*arg)[i] != '\0')
		new_arg[j++] = (*arg)[i++];
	new_arg[j] = '\0';
	free(arg);
	return (new_arg);
}
