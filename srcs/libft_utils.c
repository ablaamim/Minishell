/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:20:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/07 19:43:39 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(char const *str)
{
	size_t	len;

	len = 0x0;
	while (str[len])
		len++;
	return (len);
}

/*
 * Copy l character from source string to destination string.
*/

size_t	ft_strlcpy(char *dest, char const *src, size_t destsize)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	if (destsize > len_src)
		ft_memcpy(dest, src, len_src + 0x1);
	else if (destsize)
	{
		ft_memcpy(dest, src, destsize - 1);
		*(dest + destsize - 1) = '\0';
	}
	return (len_src);
}
/*
#include <string.h>
int	main(void)
{
	char	dest[] = "to be filled     !";
	char	src[] = "copy";
	char	dest1[] = "to be filled      !";
	char	src1[] = "copy";

	printf("|%zu|\n", ft_strlcpy(dest, src, 3));
	printf("|%s|\n", dest);
	printf("|%zu|\n", strlcpy(dest1, src1, 3));
	printf("|%s|\n", dest1);
	return (EXIT_SUCCESS);
}
*/

/*
 * Calculate max_len delimiter of a string.
*/

size_t	ft_strnlen(char const *str, size_t max_len)
{
	size_t	size;

	size = 0x0;
	if (!str)
		return (0x0);
	while (*(str + size) && max_len--)
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
	* (new + max_len) = '\0';
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
