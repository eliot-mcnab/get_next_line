/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:53:37 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 15:53:03 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stddef.h>

t_hashmap	*ft_hashmap_new(size_t size)
{
	t_hashmap	*hashmap;

	hashmap = malloc(sizeof(*hashmap));
	if (!hashmap || !size)
		return (NULL);
	hashmap -> map = malloc(size * sizeof(t_list *));
	hashmap -> size = size;
	if (!(hashmap -> map))
		return (NULL);
	while (size--)
		(hashmap -> map)[size] = NULL;
	return (hashmap);
}

void	ft_hashmap_set(t_hashmap *hashmap, size_t hash, t_any data)
{
	t_any			*hash_data;
	t_list			*slot;
	t_list			*node_current;
	static size_t	test;

	if (!hashmap)
		return ;
	hash_data = malloc(2 * sizeof(*hash_data));
	if (!hash_data)
		return ;
	test = hash;
	hash_data[0] = &test;
	hash_data[1] = data;
	slot = (hashmap -> map)[hash % (hashmap -> size)];
	if (!slot)
		(hashmap -> map)[hash % (hashmap -> size)] = ft_lst_new(hash_data);
	else
	{
		node_current = slot;
		while (node_current -> next)
			node_current = node_current -> next;
		node_current -> next = ft_lst_new(hash_data);
	}
}

t_any	*ft_hashmap_get(t_hashmap *hashmap, size_t hash)
{
	t_list	*node_current;

	node_current = (hashmap -> map)[hash % hashmap -> size];
	while (node_current && **((size_t **)node_current -> content) != hash)
		node_current = node_current -> next;
	if (!node_current)
		return (NULL);
	return (((t_any **)(node_current -> content))[1]);
}

void	ft_hashmap_clear(t_hashmap *hashmap, void (*f_free)(t_any))
{
	t_list	*node_current;

	if (!hashmap)
		return ;
	while ((hashmap -> size)--)
	{
		node_current = (hashmap -> map)[hashmap -> size];
		ft_lstclear(&node_current, f_free);
	}
	free(hashmap -> map);
	free(hashmap);
}
