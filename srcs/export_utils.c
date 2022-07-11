/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:56:51 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 20:57:59 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_get_len_var_name(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] != '+' && arg[len] != '=' && arg[len] != '\0')
		++len;
	return (len);
}

char	*get_var_value(char *str, char *env_value)
{
	char	*var_value;

	if (*(str - 2) == '+')
		var_value = ft_strjoin(env_value, str, "");
	else
		var_value = ft_strdup(str);
	return (var_value);
}

