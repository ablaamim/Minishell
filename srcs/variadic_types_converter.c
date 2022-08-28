/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variadic_types_converter.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:56:13 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/28 12:27:43 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	convert_percent(t_buffering *fmt, va_list ap)
{
	(void)ap;
	fmt->buffer[fmt->i++] = '%';
}

void	convert_c(t_buffering *fmt, va_list ap)
{
	int	c;

	c = (char)va_arg(ap, int);
	fmt->buffer[fmt->i++] = c;
}

void	convert_s(t_buffering *fmt, va_list ap)
{
	int		len;
	char	*s;

	s = va_arg(ap, char *);
	if (s == 0x0)
		s = "(null)";
	len = ft_strlen(s);
	ft_strcpy(&fmt->buffer[fmt->i], s);
	fmt->i += len;
}

void	convert_d(t_buffering *fmt, va_list ap)
{
	int		len;
	int		val;
	char	*s;

	val = va_arg(ap, int);
	s = ft_itoa(val);
	len = ft_strlen(s);
	ft_strncpy(&fmt->buffer[fmt->i], s, len);
	fmt->i += len;
	free(s);
}
