/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:21:49 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/28 12:05:43 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_arrays(char **arrays)
{
	int	i;

	i = 0x0;
	while (arrays[i])
	{
		free(arrays[i++]);
	}
	free(arrays);
}
