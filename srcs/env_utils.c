/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:01:17 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/05 05:36:53 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * TO DO : SET_ENV FUNC()
 * - SET VAR VALUE IF IT DOES NOT EXIST.
 * - Replace.
*/

void	ft_set_env_var(const char *name, const char *val, int replace)
{
	int		i;
	t_env	*env;
	t_env	temp;

	env = get_bash_env();
	temp = *env;
	i = ft_in_env(name);
	if (i >= 0x0 && replace != 0x0)
	{
		garbage_free((void **) &temp[i]);
		if (val == 0x0)
			temp[i] = ft_strjoin(name, val, "");
		else
			temp[i] = ft_strjoin(name, val, "=");
	}
	else
	{
		*env = ft_add_up_in_env(name, val, temp);
		garbage_free((void **) &temp);
	}
}
/*
 * Return index of var in environment, returns -1 if not found.
*/

int	ft_in_env(const char *var)
{
	int		i;
	int		len;
	t_env	*env;
	t_env	temp;

	i = 0x0;
	len = ft_strlen(var);
	env = get_bash_env();
	temp = *env;
	while (temp[i])
	{
		if (ft_strncmp(temp[i], var, len) == 0x0)
		{
			if (temp[i][len] == '=' || temp[i][len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

/*
 * Return value of var in environment, return NULL if its not found.
*/

char	*get_env(const char *var)
{
	t_env	temp;
	int		i;
	t_env	*env;

	i = ft_in_env(var);
	if (i == -1)
		return (0x0);
	env = get_bash_env();
	temp = *env;
	return (&temp[i][ft_strlen(var) + 1]);
}

/*
 * Rerturn address of environment.
 * [AKA WANNA BE GLOBAL //HACK IT ITS FINE]
*/

t_env	*get_bash_env(void)
{
	static t_env	bash_env = NULL;

	return (&bash_env);
}

/*
 * Calculate env length and return it.
*/

int	env_length(t_env env)
{
	int	len;

	len = 0x0;
	while (env[len])
		len++;
	return (len);
}
