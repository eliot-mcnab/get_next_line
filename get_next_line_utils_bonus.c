/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:20:59 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 11:22:25 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_larray_add(t_linkarray *linkarray, t_any data)
{
	t_list	*array_current;
	size_t	i;

	if (!linkarray)
		return ;
	array_current = linkarray -> last;
	if (linkarray -> index / ARRAY_SIZE >= linkarray -> n_array)
	{
		array_current -> next = ft_lst_new(malloc(ARRAY_SIZE * sizeof(t_any)));
		array_current = array_current -> next;
		if (!array_current)
			return ;
		linkarray -> last = array_current;
		linkarray -> n_array++;
	}
	i = (linkarray -> index) % ARRAY_SIZE;
	((t_any *)array_current -> content)[i] = data;
	linkarray -> index++;
}

static void	ft_larray_grab(t_any *grabbed, t_any *content,
		size_t *i_start, size_t i_stop)
{
	while (*i_start < i_stop)
	{
		grabbed[*i_start] = content[*i_start % ARRAY_SIZE];
		(*i_start)++;
	}
}

t_any	*ft_larray_collect(t_linkarray *linkarray)
{
	t_any	*grabbed;
	t_list	*node_current;
	size_t	i;
	size_t	j;

	if (!linkarray)
		return (NULL);
	grabbed = malloc((linkarray -> index + 1) * sizeof(*grabbed));
	if (!grabbed)
		return (NULL);
	node_current = linkarray -> first;
	i = 1;
	j = 0;
	while (i < linkarray -> n_array)
	{
		ft_larray_grab(grabbed, node_current -> content, &j,
			(j / ARRAY_SIZE + 1) * ARRAY_SIZE);
		node_current = node_current -> next;
		i++;
	}
	ft_larray_grab(grabbed, node_current -> content, &j, linkarray -> index);
	grabbed[j] = NULL;
	return (grabbed);
}

static void	ft_subarray_free(t_list *node, size_t until, void (*f_free)(t_any))
{
	size_t	i;

	i = 0;
	node -> next = NULL;
	while (i < until)
	{
		if (f_free)
			f_free(((t_any *)node -> content)[i++]);
		else
			free(((t_any *)node -> content)[i++]);
	}
	free(node -> content);
	free(node);
}

void	ft_larray_free(t_linkarray *linkarray, void (*f_free)(t_any))
{
	t_list	*node_current;
	t_list	*node_previous;

	if (!linkarray)
		return ;
	node_current = linkarray -> first;
	while (linkarray -> index > ARRAY_SIZE)
	{
		node_previous = node_current;
		node_current = node_current -> next;
		ft_subarray_free(node_previous, ARRAY_SIZE, f_free);
		linkarray -> index -= ARRAY_SIZE;
	}
	ft_subarray_free(node_current, linkarray -> index, f_free);
	linkarray -> first = NULL;
	linkarray -> index = 0;
	free(linkarray);
}
