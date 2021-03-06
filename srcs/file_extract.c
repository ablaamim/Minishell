/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:10:15 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 15:03:28 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Extract shell name from executable file.
*/

char	*file_extract(char *filepath)
{
	int	i;

	if (filepath == 0x0)
		return (0x0);
	if (ft_strchr(filepath, '/') == 0x0)
		return (filepath);
	i = ft_strlen(filepath);
	while (i > 0 && filepath[i] != '/')
		i--;
	return (&filepath[i + 1]);
}
