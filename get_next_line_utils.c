/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:43:51 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 11:02:10 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	ft_lstclear(t_list **head, void (*f_free)(t_any))
{
	t_list	*node_current;
	t_list	*node_previous;

	if (!head || !*head)
		return ;
	node_current = *head;
	while (node_current)
	{
		node_previous = node_current;
		node_current = node_current -> next;
		ft_lstdelone(node_previous, f_free);
	}
	*head = NULL;
}

void	ft_lstdelone(t_list *node, void (*f_free)(t_any))
{
	if (!node || !(node -> content))
		return ;
	node -> next = NULL;
	if (f_free)
		f_free(node -> content);
	else
		free(node -> content);
	free(node);
}
