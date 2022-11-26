/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:38:00 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/26 15:55:17 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
 * @brief Creates a new linked list node with the given content.
 *
 * @param content (void *): the content to initialise the linked list with.
 *
 * @return (t_list *): new linked list node.
 */
t_list	*ft_lst_new(void *content)
{
	t_list	*lst;

	lst = malloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

/*
 * @brief Removes a node in a linked list, removing its reference to the next
 * 	node in the list in case [lst] is still referenced somewhere else in the
 * 	program.
 *
 * @param lst (t_lst): the list to free.
 * @param f_free (void (void *)): function used to free the contents of the lits
 */
void	ft_lst_delone(t_list *lst, void (*f_free)(void *))
{
	if (!lst | ! f_free)
		return ;
	lst->next = NULL;
	f_free(lst->content);
	free(lst);
}

/*
 * @brief Frees all nodes in a linked list and sets the head of the list to
 * 	NULL.
 *
 * @param lst (t_lst **): the head of the list.
 * @param f_free (void (void *)): function used to free the contents of the lits
 */
void	ft_lst_delall(t_list **lst, void (*f_free)(void *))
{
	t_list	*node_current;
	t_list	*node_previous;

	if (!lst | !f_free)
		return ;
	node_current = *lst;
	while (node_current)
	{
		node_previous = node_current;
		node_current = node_current->next;
		ft_lst_delone(node_previous, f_free);
	}
	*lst = NULL;
}
