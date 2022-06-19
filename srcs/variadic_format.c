/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variadic_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:17:21 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/19 14:21:59 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	type_recognizer(char type, va_list ap, t_buffering *fmt)
{
	int					i;
	t_converter const	convert[] = {
	{.type = '%', .function = &convert_percent},
	{.type = 'c', .function = &convert_c},
	{.type = 's', .function = &convert_s},
	{.type = 'd', .function = &convert_d},
	{.type = '\0'}
	};

	i = 0x0;
	while (convert[i].type != type && convert[i].type != 0x0)
		i++;
	if (convert[i].type == '\0')
		return (-1);
	convert[i].function(fmt, ap);
	return (0x0);
}

char	*variadic_format(const char *str, va_list ap)
{
	int			i;
	t_buffering	fmt;

	i = 0x0;
	fmt.i = 0x0;
	ft_bzero(fmt.buffer, BUFFERING);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (type_recognizer(str[++i], ap, &fmt) == -1)
				return (0x0);
		}
		else
			fmt.buffer[fmt.i++] = str[i];
		i++;
	}
	return (ft_strdup(fmt.buffer));
}
