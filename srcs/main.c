/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:28:59 by ablaamim          #+#    #+#             */
/*   Updated: 2022/05/24 10:56:45 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	(void)	argv;
	if (argc == 1)
	{
		ft_prompt();
	}
	else
	{
		write(2, ERROR_MSG_ARG, sizeof("ERROR_MSG_ARG"));
	}
	return (EXIT_SUCCESS);
}
