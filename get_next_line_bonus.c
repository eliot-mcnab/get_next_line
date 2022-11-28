/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:35:33 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/28 14:54:07 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
 * @brief Creates a new linked string instance.
 * 
 * Linked strings are designed to avoid the overhead of resizing strings
 * by storing consecutive strings in arrays in linkedlists. Strings are then
 * concatenated all at once when the ft_linkstr_collect(1) function is called,
 * avoiding multiple resizes.
 *
 * @param linksize (size_t): the number of strings each linkedlist node will
 * 	hold.
 *
 * @return (t_linkstr *): new linked string.
 */
t_linkstr	*ft_linkstr_new(size_t linksize)
{
	t_linkstr	*linkstr;

	linkstr = malloc(sizeof(*linkstr));
	if (!linkstr || !linksize)
		return (NULL);
	linkstr->strs_first = ft_lst_new(malloc(linksize * sizeof(char *)));
	if (!linkstr->strs_first)
	{
		free(linkstr);
		return (NULL);
	}
	linkstr->strs_last = linkstr->strs_first;
	linkstr->linksize = linksize;
	linkstr->i = 0;
	return (linkstr);
}

/*
 * @brief Adds a new string at the end of a a linked string.
 *
 * @param linkstr (t_linkstr *): the linked string to append [str] to.
 * @param str (char *): the string to append to [linkstr].
 */
void	ft_linkstr_add(t_linkstr *linkstr, char *str)
{
	char	**strs;
	char	**strs_new;

	if (!linkstr | !str)
		return ;
	if (linkstr->i && linkstr->i % linkstr->linksize == 0)
	{
		strs_new = malloc(linkstr->linksize * sizeof(*strs_new));
		linkstr->strs_last->next = ft_lst_new(strs_new);
		linkstr->strs_last = linkstr->strs_last->next;
	}
	strs = (char **)linkstr->strs_last->content;
	strs[linkstr->i % linkstr->linksize] = str;
	linkstr->i++;
}

/*
 * @brief Determines the total size of a linked string by summing the individual
 * 	size of each string it contains.
 *
 * @param linkstr (t_linkstr *): the linked strings to determine the total size
 * 	of.
 *
 * @return (size_t): the total size of [linkstr].
 */
static size_t	ft_linkstr_size(t_linkstr *linkstr)
{
	t_list	*node_current;
	char	**strs;
	size_t	size;
	size_t	i;

	node_current = linkstr->strs_first;
	size = 0;
	i = 0;
	while (i < linkstr->i)
	{
		if (i && i % linkstr->linksize == 0)
			node_current = node_current->next;
		strs = (char **)node_current->content;
		size += ft_quicklen(strs[i % linkstr->linksize]);
		i++;
	}
	return (size);
}

/*
 * @brief Concatenates all strings held in a linked string into a single string.
 *
 * @param linkstr (t_linkstr *): the linked string containing the strings.
 *
 * @return (char *): result of concatenating all the strings in [linkstr].
 */
char	*ft_linkstr_collect(t_linkstr *linkstr)
{
	char	*collect;
	t_list	*cur;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!linkstr)
		return (NULL);
	collect = malloc((ft_linkstr_size(linkstr) + 1) * sizeof(*collect));
	cur = linkstr->strs_first;
	i = 0;
	j = 0;
	while (i < linkstr->i)
	{
		if (i && i % linkstr->linksize == 0)
			cur = cur->next;
		k = 0;
		while (((char **)cur->content)[i % linkstr->linksize][k])
			collect[j++] = ((char **)cur->content)[i % linkstr->linksize][k++];
		i++;
	}
	collect[j] = '\0';
	return (collect);
}

/*
 * @brief Deletes all the contents of a linked string and frees up all memory
 * 	allocated to it.
 *
 * @param linkstr (t_linkstr *): the linked string to delete.
 * @param f_free (void (void *)): function used to free the strings in
 * 	[linkstr]. Pass NULL if the strings in [linkstr] don't need to be freed.
 *
 * @return (void *): NULL.
 */
void	*ft_linkstr_delall(t_linkstr *linkstr, void (*f_free)(void *))
{
	t_list	*node_current;
	t_list	*node_previous;
	size_t	i;

	if (!linkstr)
		return (NULL);
	node_current = linkstr->strs_first;
	i = 0;
	while (i < linkstr->i)
	{
		if (i && i % linkstr->linksize == 0)
		{
			node_previous = node_current;
			node_current = node_current->next;
			ft_lst_delone(node_previous, &free);
		}
		if (f_free)
			f_free(((char **)node_current->content)[i % linkstr->linksize]);
		i++;
	}
	ft_lst_delone(node_current, &free);
	linkstr->strs_first = NULL;
	free(linkstr);
	return (NULL);
}
