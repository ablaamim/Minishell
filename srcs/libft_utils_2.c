/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:20:38 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/10 17:24:25 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup(char *str)
{
	int		i;
	int		len;
	char	*new;

	if (str == 0x0)
		return (0x0);
	i = -1;
	len = ft_strlen(str);
	new = (char *) malloc(sizeof(str) + 1);
	if (new == 0x0)
		return (0x0);
	while (++i < len)
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}
