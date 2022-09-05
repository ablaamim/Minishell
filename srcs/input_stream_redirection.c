/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stream_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:07:06 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/05 17:29:16 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int input_stream_redirection(const char *io_stream)
{
	int file_descriptor;

	file_descriptor = open(io_stream, O_RDONLY);
	if (file_descriptor < 0)
	{
		variadic_error_printer(2, "Minishell : %s : No such file or \
				directory\n",
							   io_stream);
		exit_value_set(EXIT_FAILURE);
		return (-1);
	}
	return (file_descriptor);
}
