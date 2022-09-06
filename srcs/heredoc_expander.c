/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:29:19 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 20:40:14 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// expand heredocument

void	heredoc_expander(char **argv)
{
	char	*variable_name;
	char	*variable_value;
	char	*tmp;
	int		i;

	i = 0x0;
	while ((*argv)[i] != '\0')
	{
		if ((*argv)[i] == '$')
		{
			if ((*argv)[i] == '\0' || ft_isalnum((*argv)[i + 0x1]) == 0x0)
				*argv = new_argument(argv, 0x0, i++, "$");
			else
			{
				get_variable_name_and_val(*argv + i, &variable_name,
					&variable_value);
				tmp = ft_strdup(*argv);
				free(*argv);
				*argv = new_argument(&tmp, ft_strlen(variable_name),
						i, variable_value);
				free(tmp);
				i += ft_strlen(variable_value);
				garbage_free((void **)&variable_name);
			}
		}
		else
			++i;
	}
}
