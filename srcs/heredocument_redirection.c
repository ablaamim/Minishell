/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocument_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:04:10 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/29 16:16:50 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc_redir(char const *stream, bool input_had_quotes)
{
	//char	*doc;
	//int		fd[2];

	//doc = heredocument(stream);
	input_had_quotes = false;
	stream = 0x0;
	if (input_had_quotes == false && stream == 0x0)
		input_had_quotes = true;
	return (1);
}
