/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:17:10 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/15 12:28:47 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strstr(const char	*big, const char	*little)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *) big);
	j = 0x0;
	while (big[j] != '\0')
	{
		if (big[j] == little[0])
		{
			i = 0x1;
			while (little[i] != '\0' && big[j + i] == little[i])
				++i;
			if (little[i] == '\0')
				return((char *)&big[j]);
		}
		j++;
	}
	return (0x0);
}

char	*ft_strchr(const char	*s, int	c)
{
	unsigned int	i;

	i = 0x0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return(0x0);
}
