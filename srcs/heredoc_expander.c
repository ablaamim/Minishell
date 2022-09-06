/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:29:19 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 22:41:58 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	increment_and_free(int i, char *var_value, char *var_name)
{
	i += ft_strlen(var_value);
	garbage_free((void **) &var_name);
}

void	heredoc_expander(char **argv)
{
	char	*var_name;
	char	*var_value;
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
				get_variable_name_and_val(*argv + i, &var_name, &var_value);
				tmp = ft_strdup(*argv);
				free(*argv);
				*argv = new_argument(&tmp, ft_strlen(var_name), i, var_value);
				free(tmp);
				increment_and_free(i, var_value, var_name);
			}
		}
		else
		++i;
	}
}
