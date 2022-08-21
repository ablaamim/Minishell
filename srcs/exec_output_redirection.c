/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_output_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:12:49 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/21 15:52:01 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// SEGV IN FUNCTION

int	exec_output_redirection(char **input)
{
	int	open_flag;
	int	fd;

	printf("WHY SEGV ???\n\n");
	if (ft_strcmp(">", *input) == 0x0)
		open_flag = O_TRUNC; // output redir >
	else
		open_flag = O_APPEND; // append redir >>
	++input;
	fd = open(*input, O_WRONLY | O_CREAT | open_flag, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	// MANAGE ERROR
	if (fd < 0x0)
	{
		variadic_error_printer(2, "minishell : %s", IN_REDIR);
		exit_value_set(EXIT_FAILURE);
		return (ERR);
	}
	return (fd);
}
