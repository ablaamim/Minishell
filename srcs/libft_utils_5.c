/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:06:09 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/28 12:28:07 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_isspace(int c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

bool has_space(char *str)
{
	while (*str != '\0')
		if (ft_isspace(*(str++)))
			return (true);
	return (false);
}

void array_free(char ***array)
{
	int i;

	i = 0;
	while ((*array)[i] != NULL)
	{
		garbage_free((void **)&(*array)[i]);
		++i;
	}
}

char *ft_substr(const char *src, unsigned int start, size_t len)
{
	char *r;
	size_t i;
	size_t len_src;

	i = 0;
	if (!src)
		return (NULL);
	len_src = ft_strlen(src);
	if (start > len_src)
		return (ft_strdup(""));
	if (len_src < len)
		r = (char *)malloc((len_src + 1) * sizeof(*src));
	else
		r = (char *)malloc((len + 1) * sizeof(*src));
	if (!r)
		return (NULL);
	while (i < len)
	{
		if (!src[i + start])
			return (r);
		r[i] = src[i + start];
		i++;
	}
	r[i] = '\0';
	return (r);
}