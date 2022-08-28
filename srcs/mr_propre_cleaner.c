/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_propre_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:36:30 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/28 12:13:05 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * LEAKS FIGHTER, ALL BECAUSE WE LOVE MEMORY AND HATE LEAKS.
 * [MIGHT BE CAUSING PROBLEMS]
*/

void	cleaner_mr_propre(char	*tmp_path, char	*shell_path, \
		char	*shlvl_value)
{
	free(tmp_path);
	free(shell_path);
	free(shlvl_value);
}
