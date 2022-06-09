/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:20:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/09 13:06:26 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strnlen(char const *str, size_t max_len)
{
	size_t	size;

	size = 0x0;
	if (!str)
		return (0x0);
	while (str[size] && max_len--)
		size++;
	return (size);
}

/*
int	main(void)
{
	char str[] = "CALC N LEN OF ME";

	printf("%zu\n", ft_strnlen(str, 4));
}
*/

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	unsigned char	*tmp;

	if (!dest || !src)
		return (0x0);
	tmp = dest;
	while (n--)
		*tmp++ = *(unsigned char *) src++;
	return (dest);
}

char	*ft_strndup(const char *str, size_t n)
{
	char	*new;
	size_t	max_len;

	if (!str)
		return (0x0);
	max_len = ft_strnlen(str, n);
	new = 0x0;
	new = garbage_malloc(sizeof(*str) * (max_len + 1));
	new[max_len] = '\0';
	return (ft_memcpy(new, str, max_len));
}
/*
int	main()
{
	char	str[] = "DUP N SIZE OF MEEEEEE!";
	printf("|%s|\n", str);
	printf("|%s|\n", ft_strndup(str, 2));
}
*/
