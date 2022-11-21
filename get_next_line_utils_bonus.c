/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:20:59 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/21 19:16:48 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lst_new(t_any content)
{
	t_list	*node;

	node = malloc(sizeof(*node));
	if (!node)
	{
		return (NULL);
	}
	node -> content = content;
	node -> next = NULL;
	return (node);
}

t_linkarray	*ft_larray_new(t_any *data, size_t n)
{
	t_linkarray	*linkarray;
	size_t		i;

	linkarray = malloc(sizeof(*linkarray));
	if (!linkarray)
	{
		return (NULL);
	}
	linkarray -> array = ft_lst_new(malloc(ARRAY_SIZE * sizeof(t_any)));
	linkarray -> last = linkarray -> array;
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
	node_current = linkarray -> array;
	while (linkarray -> index > ARRAY_SIZE)
	{
		node_previous = node_current;
		node_current = node_current -> next;
		ft_subarray_free(node_previous, ARRAY_SIZE, f_free);
		linkarray -> index -= ARRAY_SIZE;
	}
	ft_subarray_free(node_current, linkarray -> index, f_free);
	linkarray -> array = NULL;
	linkarray -> index = 0;
	free(linkarray);
}
