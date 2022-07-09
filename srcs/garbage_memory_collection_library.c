/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_memory_collection_library.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:11:06 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/09 18:03:46 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	garbage_free(void **garbage_to_free)
{
	t_garbage_list	**garbage_list;
	t_garbage_list	*current;
	t_garbage_list	*previous;

	previous = NULL;
	if (*garbage_to_free != NULL && garbage_to_free != NULL)
	{
		garbage_list = get_garbage_list();
		current = *garbage_list;
		while (current->ptr != *garbage_to_free)
		{
			previous = current;
			current = current->next;
		}
		if (previous == NULL)
			*garbage_list = current->next;
		else
			previous->next = current->next;
		garbage_memdel((void **)&current->ptr);
		garbage_memdel((void **)&current);
		*garbage_to_free = NULL;
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
	new = malloc(sizeof(t_garbage_list) * 0x1);
	if (new == NULL)
		garbage_exit(EXIT_FAILURE, "Error : malloc() failed.\n");
	garbage_bzero(new, sizeof(t_garbage_list) * 0x1);
	new->ptr = malloc(size);
	if (new->ptr == 0x0)
	{
		garbage_memdel((void **)&new);
		garbage_exit(EXIT_FAILURE, "Error : malloc() failed.\n");
	}
	garbage_bzero(new->ptr, size);
	new->next = tmp;
	*garbage_list = new;
	return (new->ptr);
}
