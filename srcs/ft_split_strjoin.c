/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_strjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:40:02 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/29 17:39:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2, char const *sep)
{
	int		size;
	char	*strnew;

	if (!s1)
	{
		if (!s2)
			return (NULL);
		return (ft_strjoin(sep, s2, ""));
	}
	if (!s2)
		return (ft_strjoin(s1, sep, ""));
	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(sep);
	if (s1[0] == '\0' && s2[0] == '\0')
		return (ft_strdup(""));
	strnew = garbage_malloc(sizeof(char) * (size + 1));
	ft_strcpy(strnew, (char *)s1);
	ft_strcat(strnew, (char *)sep);
	ft_strcat(strnew, (char *)s2);
	return (strnew);
}

static int	ft_nb_split(char *str, char c)
{
	int	i;
	int	nb;
	int	bl;

	i = 0;
	nb = 0;
	while (str[i])
	{
		bl = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			if (!bl)
				nb += 1;
			bl = 1;
			i++;
		}
	}
	return (nb);
}

static char	*ft_cut_split(char *str, char c, int *i)
{
	int		j;
	int		len;
	char	*strnew;

	j = 0;
	len = 0;
	while (str[*i] == c && str[*i])
		*i += 1;
	while (str[*i + len] != c && str[*i + len])
		len++;
	strnew = garbage_malloc(sizeof(char) * (len + 1));
	while (j < len)
	{
		strnew[j] = str[*i];
		j++;
		*i += 1;
	}
	strnew[j] = '\0';
	return (strnew);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	char	**tab;
	int		offset;
	int		tab_size;

	i = 0;
	offset = 0;
	if (!str)
		return (NULL);
	tab_size = ft_nb_split((char *)str, c);
	tab = garbage_malloc(sizeof(char *) * (tab_size + 1));
	while (i < tab_size)
	{
		tab[i] = ft_cut_split((char *)str, c, &offset);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
