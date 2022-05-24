/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:35:21 by ablaamim          #+#    #+#             */
/*   Updated: 2022/05/24 19:00:26 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_save_history(char	*buffer)
{
	if (buffer && *buffer)
		add_history(buffer);
}

int	read_input_buffer(void)
{
	char	*buffer;
	int		check_returns;

	check_returns = 0x1;
	buffer = readline("minishell$>");
	if (!buffer)
		return (0x0);
	ft_save_history(buffer);
	free(buffer);
	return (check_returns);
}

void	ft_prompt(void)
{
	int	check_returns;

	check_returns = 0x0;
	while (0x1)
	{
		check_returns = read_input_buffer();
		if (!check_returns)
			write(2, EXIT_MINISHELL, sizeof(EXIT_MINISHELL));
	}
}
