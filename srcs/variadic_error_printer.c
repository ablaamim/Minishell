/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variadic_error_printer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:08:57 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/19 14:55:38 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	variadic_error_printer(int	fd, const char	*fmt, ...)
{
	int		len;
	char	*s;
	va_list	ap;

	va_start(ap, fmt);
	s = variadic_format(fmt, ap);
	len = ft_putstr_fd(s, fd);
	garbage_free((void **)&s);
	return (len);
}

int	main(void)
{
	variadic_error_printer(2, "EXIT MINISHELL\n");
	return (EXIT_SUCCESS);
}
