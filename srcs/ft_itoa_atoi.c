/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:19:03 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/18 12:21:22 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_number_len(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*strnew;

	i = ft_number_len(n);
	strnew = garbage_malloc(sizeof(char) * (i + 1));
	strnew[i--] = '\0';
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		strnew[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		strnew[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (strnew);
}

int	ft_atoi(const char *s)
{
	long	res;
	int		sign;

	sign = 1;
	res = 0;
	if (s == NULL)
		return (0);
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '-')
		sign *= -1;
	if (*s == '+' || *s == '-')
		s++;
	while (*s >= 48 && *s <= 57)
	{
		res = res * 10 + *s - 48;
		s++;
	}
	return (res * sign);
}
