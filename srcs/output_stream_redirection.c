/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_stream_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:18:30 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/20 23:44:57 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	output_stream_redirection(char **arguments)
{
	int	file_descriptor;
	int	mark;

	if (ft_strcmp(">", *arguments) == 0x0)
		mark = O_TRUNC;
	else
		mark = O_APPEND;
	++arguments;
	file_descriptor = open(*arguments, O_WRONLY | O_CREAT | mark |\
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (file_descriptor < 0x0)
	{
		variadic_error_printer(2, "Minishell : %s : No such file\
				or directory\n", *arguments);
		exit_value_set(EXIT_FAILURE);
		return (-1);
	}
	return (file_descriptor);
}
