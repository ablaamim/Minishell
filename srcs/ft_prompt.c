/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:35:21 by ablaamim          #+#    #+#             */
/*   Updated: 2022/05/24 12:42:49 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_save_history(char	*input)
{
	if (input && *input)
		add_history(input);
}

int	read_input(void)
{
	char	*input_readline;
	int		check_returns;

	check_returns = 0x1;
	input_readline = readline("minishell$>");
	if (!input_readline)
		return (0x0);
	ft_save_history(input_readline);
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
			write(2, EXIT_MINISHELL, sizeof(EXIT_MINISHELL));
	}
}
