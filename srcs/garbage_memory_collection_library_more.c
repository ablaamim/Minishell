/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_memory_collection_library_more.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:48:04 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/28 12:08:11 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	garbage_exit(int status, char *msg)
{
	if (msg != 0x0)
	{
		if (status == EXIT_FAILURE)
			write(2, "Error : ", sizeof("Error : "));
		write(2, msg, sizeof(msg));
		write(2, "\n", 1);
	}
	exit(status);
}

void	garbage_free_everything(void)
{
	t_garbage_list	**garbage;
	t_garbage_list	*current;
	t_garbage_list	*next;

	garbage = get_garbage_list();
	current = *garbage;
	while (current)
	{
		next = current->next;
		garbage_memdel((void **) &current->ptr);
		garbage_memdel((void **) &current);
		current = next;
	}
}
