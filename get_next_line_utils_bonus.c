/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:38:00 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/26 13:45:19 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	ft_lst_delone(t_list *lst, void (*f_free)(void *))
{
	if (!lst | ! f_free)
		return ;
	lst->next = NULL;
	f_free(lst->content);
	free(lst);
}

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
