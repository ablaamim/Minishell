/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_up_in_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:18:07 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/02 15:11:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_length_special(t_env *env)
{
	int	len = 0x0;
	while ((*env)[len])
		len++;
	return (len);
}

t_env	ft_add_up_in_env(const char *name, const char *val, t_env env)
{
	int		i;
	t_env	new_env;

	printf("ADD UP IN ENV FUNC\n");
	i = 0x0;
	new_env = garbage_malloc(sizeof(char *) * (env_length(env) + 2));
	while (env[i])
	{
		//printf("%s\n", (*env)[i]);
		new_env[i] = env[i];
		i++;
	}
	if (val == 0x0)
		new_env[i++] = ft_strjoin(name, val, "");
	else
		new_env[i++] = ft_strjoin(name, val, "=");
	new_env[i] = NULL;
	//ft_print_env(new_env);
	return (new_env);
}
