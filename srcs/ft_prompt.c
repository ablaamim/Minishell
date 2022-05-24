/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:35:21 by ablaamim          #+#    #+#             */
/*   Updated: 2022/05/24 10:45:16 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_input(void)
{
	char	*input_readline;
	int		check_returns;

	check_returns = 0x1;
	input_readline = readline("minishell$>");
	if (!input_readline)
		return (0x0);
	add_history(input_readline);
	free(input_readline);
	return (check_returns);
}

void	ft_prompt(void)
{
	int	check_returns;

	check_returns = 0x0;
	while (0x1)
	{
		check_returns = read_input();
		if (!check_returns)
			write(2, "exit minishell\n", sizeof("exit minishell\n"));
	}
}
