/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:20:38 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/25 01:06:12 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_stringjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (joined == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j] != '\0')
	{
		joined[i++] = s1[j];
		j++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		joined[i++] = s2[j];
		j++;
	}
	joined[i] = '\0';
	return (joined);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		size;
	char	*dup;

	i = 0;
	if (s == NULL)
		size = 1;
	else
		size = ft_strlen(s);
	dup = garbage_malloc(sizeof(char) * (size + 1));
	if (s != NULL)
	{
		while (s[i])
		{
			dup[i] = s[i];
			i++;
		}
	}
	dup[i] = '\0';
	return (dup);
}

/*
char	*ft_strdup(const char *s)
{
	int		len;
	char	*dest;
	int		i;

	i = 0;
	len = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	dest = (char *) malloc(sizeof (*s) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
*/

/*
char	*ft_strdup(char *str)
{
	int		i;
	int		len;
	char	*new;

	if (str == 0x0)
		return (0x0);
	i = -1;
	len = ft_strlen(str);
	new = (char *) malloc(sizeof(char) + 1);
	if (new == 0x0)
		return (0x0);
	while (++i < len)
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}
*/
/*
int	main()
{
	char	str[] = "this is to dup";

	printf("|%s|\n", ft_strdup(str));
}
*/
