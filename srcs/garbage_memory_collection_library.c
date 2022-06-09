/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_memory_collection_library.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:11:06 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/09 12:11:44 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	garbage_free(void **garbage_to_free)
{
	t_garbage_list	**garbage_list;
	t_garbage_list	*current;
	t_garbage_list	*previous;

	previous = 0x0;
	if (*garbage_to_free != 0x0 && garbage_to_free != 0x0)
	{
		garbage_list = get_garbage_list();
		current = *garbage_list;
		while (current->ptr != *garbage_to_free)
		{
			previous = current;
			current = current->next;
		}
		if (previous == 0x0)
			*garbage_list = current->next;
		else
			previous->next = current->next;
		garbage_memdel((void **) &current->next);
		garbage_memdel((void **) &current->ptr);
		*garbage_to_free = 0x0;
	}
}

t_garbage_list	**get_garbage_list(void)
{
	static t_garbage_list	*garbage_list = NULL;

	return (&garbage_list);
}

void	garbage_bzero(void *memory, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *) memory;
	i = 0x0;
	while (i < n)
	{
		ptr[i] = 0x0;
		i++;
	}
}

void	garbage_memdel(void **memory)
{
	if (memory && *memory)
	{
		free(*memory);
		*memory = NULL;
	}
}

void	*garbage_malloc(size_t size)
{
	t_garbage_list	*tmp;
	t_garbage_list	*new;
	t_garbage_list	**garbage_list;

	new = 0x0;
	garbage_list = get_garbage_list();
	tmp = *garbage_list;
	new = malloc(sizeof(t_garbage_list));
	if (new == 0x0)
	{
		write(2, MALLOC_ERROR, sizeof(MALLOC_ERROR));
		exit(EXIT_FAILURE);
	}
	garbage_bzero(new, sizeof(t_garbage_list));
	new->ptr = malloc(size);
	if (new->ptr == 0x0)
	{
		garbage_memdel((void **) &new);
		write(2, MALLOC_ERROR, sizeof(MALLOC_ERROR));
		exit(EXIT_FAILURE);
	}
	garbage_bzero(new->ptr, size);
	new->next = tmp;
	*garbage_list = new;
	return (new->ptr);
}
