/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_catcher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:50:42 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/29 18:52:02 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	sigint_catcher(char *doc, char *line)
{
	if (*retrieve_signumber() == SIGINT)
	{
		free(line);
		free(doc);
		return (true);
	}
	return (false);
}
