/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_propre_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:36:30 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/19 15:50:52 by ablaamim         ###   ########.fr       */
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
	//printf("\n\nFREE ALL GARBAGE LEAKED\n\n");
	free(tmp_path);
	free(shell_path);
	free(shlvl_value);
	//garbage_free((void **) &tmp_path);
	//garbage_free((void **) &shell_path);
	//garbage_free((void **) &shlvl_value);
	//printf("\n\n!!!OR CAUSE PROBLEMS!!!\n\n");
}
