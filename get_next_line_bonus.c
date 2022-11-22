/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:53:37 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 16:04:30 by emcnab           ###   ########.fr       */
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
	if (!(hashmap -> map))
		return (NULL);
	hashmap -> size = size;
	while (size--)
		(hashmap -> map)[size] = NULL;
	return (hashmap);
}

static t_hashdata	*ft_hashdata_new(size_t hash, t_any data)
{
	t_hashdata	*hashdata;

	hashdata = malloc(sizeof(*hashdata));
	if (!hashdata)
		return (NULL);
	hashdata -> hash = hash;
	hashdata -> data = data;
	return (hashdata);
}

void	ft_hashmap_set(t_hashmap *hashmap, size_t hash, t_any data)
{
	t_hashdata	*hashdata;
	t_list		*slot;
	t_list		*node_current;

	if (!hashmap)
		return ;
	hashdata = ft_hashdata_new(hash, data);
	if (!hashdata)
		return ;
	slot = (hashmap -> map)[hash % (hashmap -> size)];
	if (!slot)
		(hashmap -> map)[hash % (hashmap -> size)] = ft_lst_new(hashdata);
	else
	{
		node_current = slot;
		while (node_current -> next)
			node_current = node_current -> next;
		node_current -> next = ft_lst_new(hashdata);
	}
}

t_any	*ft_hashmap_get(t_hashmap *hashmap, size_t hash)
{
	t_list		*node_current;
	t_hashdata	*hashdata;

	node_current = (hashmap -> map)[hash % hashmap -> size];
	hashdata = (t_hashdata *)node_current -> content;
	while (node_current && hashdata -> hash != hash)
	{
		node_current = node_current -> next;
		hashdata = (t_hashdata *)node_current -> content;
	}
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
