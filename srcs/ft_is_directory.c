/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:16:43 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 17:27:00 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_directory(char *binary_path)
{
	struct stat	data;

	if (stat(binary_path, &data) == -1)
		return (-1);
	if (S_ISDIR(data.st_mode) == 1)
		return (1);
	return (0);
}
