/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:35:33 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/26 14:54:32 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_linkstr	ft_linkstr_new(size_t linksize)
{
	t_linkstr	linkstr;

	linkstr.strs_first = ft_lst_new(malloc(linksize * sizeof(char *)));
	linkstr.strs_last = linkstr.strs_first;
	linkstr.linksize = linksize;
	linkstr.linkcount = 1;
	linkstr.i = 0;
	return (linkstr);
}

void	ft_linkstr_add(t_linkstr linkstr, char *str)
{
	char	**strs;
	char	**strs_new;

	if ((linkstr.i + 1) % (linkstr.linksize + 1) == 0)
	{
		strs_new = malloc(linkstr.linksize * sizeof(*strs_new));
		linkstr.strs_last->next = ft_lst_new(strs_new);
		linkstr.strs_last = linkstr.strs_last->next;
	}
	strs = (char **)linkstr.strs_last->content;
	strs[linkstr.i % linkstr.linksize] = str;
	linkstr.i++;
}

static size_t	ft_linkstr_size(t_linkstr linkstr)
{
	t_list	*node_current;
	char	**strs;
	size_t	size;
	size_t	i;

	node_current = linkstr.strs_first;
	size = 0;
	i = 0;
	while (i < linkstr.i)
	{
		if ((i + 1) % (linkstr.linksize + 1) == 0)
			node_current = node_current->next;
		strs = (char **)node_current->content;
		size += ft_quicklen(strs[i % linkstr.linksize]);
		i++;
	}
	return (size);
}

char	*ft_linkstr_collect(t_linkstr linkstr)
{
	char	*collect;
	t_list	*node_current;
	size_t	i;
	size_t	j;
	size_t	k;

	collect = malloc((ft_linkstr_size(linkstr) + 1) * sizeof(*collect));
	node_current = linkstr.strs_first;
	i = 0;
	j = 0;
	while (i < linkstr.i)
	{
		if ((i + 1) % (linkstr.linksize + 1) == 0)
			node_current = node_current->next;
		k = 0;
		while (((char **)node_current->content)[i][k])
			collect[j++] = ((char **)node_current->content)[i][k++];
	}
	collect[j] = '\0';
	return (collect);
}
