/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:29:54 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/09 18:29:54 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*alloc_new_argument(char *arg, int len_var_name, char *var_value)
{
	char	*new_arg;
	int		len_var_value;

	len_var_value = ft_strlen(var_value);
	new_arg = garbage_malloc(sizeof(*new_arg)
			* (ft_strlen(arg) - len_var_name + len_var_value));
	return (new_arg);
}

char	*fill_new_argument(char **arg, int len_var_name, int i, char *var_value)
{
	int		j;
	int		k;
	char	*new_arg;

	j = 0;
	new_arg = alloc_new_argument(*arg, len_var_name, var_value);
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