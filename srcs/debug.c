/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:06:55 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/07 11:09:05 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_env(char **env)
{
	int	param;

	if (!*env || !env)
		exit(EXIT_FAILURE);
	param = 0x0;
	while (env[param])
	{
		printf("%s\n", env[param]);
		param++;
	}
}
