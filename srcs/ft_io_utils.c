/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 21:48:22 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/19 22:05:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Init input_stream/output_stream statically in data area.
*/

t_io_streams_file	*retrieve_io(void)
{
	static t_io_streams_file	save =
	{
		.input_stream = -1,
		.output_stream = -1
	};

	return (&save);
}

/*
 * Duplicate fds and close them.
 *
 * [ TEST WITH lsof | grep "minishell" ]
*/

void	ft_close_fd(t_io_streams_file saver)
{
	dup2(saver.input_stream, 0);
	dup2(saver.output_stream, 1);
	close(saver.input_stream);
	close(saver.output_stream);
}
