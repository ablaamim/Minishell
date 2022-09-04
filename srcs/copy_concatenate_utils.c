/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_concatenate_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:18:43 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/04 21:27:14 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(dest);
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, char *src, int size)
{
	int	i;

	i = 0x0;
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*export_variable_name(char *argument)
{
	int		i;
	int		j;
	char	*var_name;

	i = 0x0;
	j = 0x0;
	if (ft_isalpha(argument[i]) == 0x0 && argument[i] != '_')
		return (0x0);
	var_name = garbage_malloc(sizeof(*var_name) * (export_len_name(argument) + 1));
	while (argument[i] != '+' && argument[i] != '=' && argument[i] != '\0')
	{
		if (ft_isalnum(argument[i]) == 0x0)
		{
			garbage_free((void **)&var_name);
			return (0x0);
		}
		else
			var_name[j++] = argument[i];
		++i;
	}
	var_name[i] = '\0';
	if (argument[i] == '+' && argument[i + 1] != '=')
		garbage_free((void **)&var_name);
	return (var_name);
}

void	export_perror(char *args, int *ret)
{
	variadic_error_printer(2, "Minishell : export : '%s' not a valid identifier\n", args);
	*ret = EXIT_FAILURE;
}
