/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:47 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/27 16:14:08 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_append_char(char *str, char c)
{
	int		i;
	char	*new_str;

	i = 0x0;
	new_str = garbage_malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

int	get_next_line(int fd, char **line)
{
	char	c;
	int		ret;
	char	*str;

	c = '\0';
	ret = 0x1;
	str = garbage_malloc(sizeof(char) * 0x1);
	str[0] = '\0';
	while (c != '\n' && ret != 0x0)
	{
		ret = read(fd, &c, 0x1);
		if (ret == -1 || c == '\0')
		{
			free(str);
			return (-1);
		}
		else if (c != '\n' && ret != 0x0)
			str = ft_append_char(str, c);
	}
	*line = str;
	return (ret);
}
