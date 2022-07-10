/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:05:57 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 17:09:43 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtins_executor(int argc, char **argv, t_io_streams_file saver)
{
	(void) argc;
	if (ft_strcmp(argv[0], "exit") == 0x0)
		ft_close_fd(saver);
	return (EXIT_SUCCESS);
}
