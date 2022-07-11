/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:21:45 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 19:23:42 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(int argc, char **argv)
{
	int		i;
	t_env	*env;

	(void)(argc && argv);
	i = 0;
	env = get_bash_env();
	while ((*env)[i])
	{
		if (ft_strchr((*env)[i], '=') != NULL)
		{
			ft_putstr((*env)[i]);
			ft_putchar('\n');
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

