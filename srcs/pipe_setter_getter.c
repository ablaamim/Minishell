/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setter_getter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 03:38:48 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/21 03:44:51 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	*ft_pipe_getter(void)
{
	static bool	piped = false;

	return (&piped);
}

void	ft_pipe_setter(bool val)
{
	bool	*piped;

	piped = ft_pipe_getter();
	*piped = val;
}
