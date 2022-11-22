/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:20:59 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 15:53:01 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_linkarray	*ft_larray_new(t_any *data, size_t n)
{
	t_linkarray	*linkarray;
	size_t		i;

	linkarray = malloc(sizeof(*linkarray));
	if (!linkarray)
	{
		return (NULL);
	}
	linkarray -> first = ft_lst_new(malloc(ARRAY_SIZE * sizeof(t_any)));
	linkarray -> last = linkarray -> first;
	linkarray -> index = 0;
	linkarray -> n_array = 1;
	i = 0;
	while (n--)
	{
		ft_larray_add(linkarray, data[i++]);
	}
	return (linkarray);
}

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

void	ft_larray_clear(t_linkarray *linkarray, void (*f_free)(t_any))
{
	t_list	*node_current;
	t_list	*node_previous;
	size_t	i;

	if (!linkarray || !f_free)
		return ;
	node_current = linkarray -> first;
	while (linkarray -> n_array--)
	{
		node_previous = node_current;
		node_current = node_current -> next;
		i = 0;
		while (i < ARRAY_SIZE)
			f_free(((t_any *)node_previous -> content)[i++]);
		ft_lstdelone(node_previous, f_free);
	}
	i = 0;
	while (i < linkarray -> index % ARRAY_SIZE)
		f_free(((t_any *)node_current -> content)[i++]);
	ft_lstdelone(node_current, f_free);
	linkarray -> first = NULL;
	linkarray -> index = 0;
	free(linkarray);
}
