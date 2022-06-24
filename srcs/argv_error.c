/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:30:51 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/24 09:39:58 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	argv_error_handler(char *argv)
{
	char *err;

	errno = EINVAL;
	err = ft_strcat(argv, ": Feature not supported");
	if (!err)
		return (0x1);
	perror(err);
	return (0x1);
}
