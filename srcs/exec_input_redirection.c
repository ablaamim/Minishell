/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:00:26 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/21 15:51:45 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_input_redirection(char *input)
{
	int	fd;

	//printf("open stream for input redir\n\n");
	fd = open(input, O_RDONLY); //input is read only of course
	// error handling.
	if (fd < 0)
	{
		variadic_error_printer(2, "minishell : %s", IN_REDIR);
		exit_value_set(EXIT_FAILURE); // SET EXIT VAL
		return (-1);
	}
	return (fd);
}
