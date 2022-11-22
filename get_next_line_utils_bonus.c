/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:20:59 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 18:51:31 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_linkarray	*ft_larray_new(size_t size)
{
	t_linkarray	*linkarray;
	size_t		i;

	linkarray = malloc(sizeof(*linkarray));
	if (!linkarray)
	{
		return (NULL);
	}
	linkarray -> i = 0;
	linkarray -> array_count = 1;
	linkarray -> array_size = size;
	linkarray -> first = ft_lst_new(malloc(size * sizeof(t_any)));
	linkarray -> last = linkarray -> first;
	i = 0;
	return (linkarray);
}

void	ft_larray_add(t_linkarray *linkarray, t_any data)
{
	t_list	*array_current;
	size_t	array_size;
	size_t	i;

	if (!linkarray)
		return ;
	array_size = linkarray -> array_size;
	array_current = linkarray -> last;
	if (linkarray -> i / array_size >= linkarray -> array_count)
	{
		array_current -> next = ft_lst_new(malloc(array_size * sizeof(t_any)));
		array_current = array_current -> next;
		if (!array_current)
			return ;
		linkarray -> last = array_current;
		linkarray -> array_count++;
	}
	i = (linkarray -> i) % array_size;
	((t_any *)array_current -> content)[i] = data;
	linkarray -> i++;
}

t_any	*ft_larray_collect(t_linkarray *a)
{
	t_any	*grabbed;
	t_list	*node_current;
	size_t	i;
	size_t	j;
	size_t	limit;

	if (!a)
		return (NULL);
	grabbed = malloc((a->i + 1) * sizeof(*grabbed));
	if (!grabbed)
		return (NULL);
	node_current = a->first;
	j = 0;
	while (j < a->i)
	{
		i = 0;
		limit = a->array_size;
		if (j >= a->i / a->array_size * a->array_size)
			limit = a->i % a->array_size;
		while (i < limit)
			grabbed[j++] = ((t_any *)node_current->content)[i++];
		node_current = node_current->next;
	}
	grabbed[a->i] = NULL;
	return (grabbed);
}

void	ft_larray_clear(t_linkarray *a, void (*f_free)(t_any))
{
	t_list	*node_current;
	t_list	*node_previous;
	size_t	i;

	if (!a || !f_free)
		return ;
	node_current = a->first;
	while (a->i >= a->array_size && a->array_count--)
	{
		node_previous = node_current;
		node_current = node_current->next;
		i = 0;
		while (i < (a->array_size))
			f_free(((t_any *)node_previous->content)[i++]);
		ft_lstdelone(node_previous, f_free);
	}
	i = 0;
	while (i < a->i % a->array_size)
		f_free(((t_any *)node_current->content)[i++]);
	ft_lstdelone(node_current, f_free);
	a->first = NULL;
	a->i = 0;
	free(a);
}
