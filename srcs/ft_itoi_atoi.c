/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoi_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:19:03 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/18 12:21:22 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_get_digit(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		count++;
	while (n != 0)
	{
		n /= 10 ;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*nstr;
	size_t		dgt;
	long int	nb;

	nb = n;
	dgt = ft_get_digit(n);
	if (n < 0)
	{
		nb *= -1;
		dgt++;
	}
	nstr = (char *)malloc(sizeof(char) * (dgt + 1));
	if (!nstr)
		return (NULL);
	nstr[dgt] = '\0';
	while (dgt--)
	{
		nstr[dgt] = nb % 10 + '0';
		nb /= 10 ;
	}
	if (n < 0)
		nstr [0] = '-';
	return (nstr);
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
