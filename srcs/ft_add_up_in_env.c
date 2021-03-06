/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_up_in_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:18:07 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/18 13:22:43 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_add_up_in_env(const char	*name, const char	*val, t_env	env)
{
	int		i;
	t_env	new_env;

	i = 0x0;
	new_env = malloc(sizeof(char *) * (env_length(env) + 2));
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	if (val == 0x0)
		new_env[i++] = ft_strjoin(name, val, "");
	else
		new_env[i++] = ft_strjoin(name, val, "=");
	new_env[i] = 0x0;
	return (new_env);
}
