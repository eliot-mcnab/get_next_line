/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:09:32 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 18:19:32 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_bonus.h"
#include "libft.h"

static void	ft_linkhash_clear(t_any any)
{
	t_hashdata	*hashdata;

	hashdata = (t_hashdata *)any;
	ft_larray_clear((t_linkarray *)hashdata -> data, &free);
	free(any);
}

int	main(void)
{
	t_linkarray	*linkarray;
	t_hashmap	*hashmap;
	char		**strs;
	size_t		i;

	linkarray = ft_larray_new(5);
	ft_larray_add(linkarray, ft_strdup("test"));
	ft_larray_add(linkarray, ft_strdup("hello"));
	ft_larray_add(linkarray, ft_strdup("nope"));
	ft_larray_add(linkarray, ft_strdup("yoooo"));
	hashmap = ft_hashmap_new(32);
	ft_hashmap_set(hashmap, 0, linkarray);
	linkarray = (t_linkarray *)ft_hashmap_get(hashmap, 0);
	strs = (char **)ft_larray_collect(linkarray);
	i = 0;
	while (strs[i])
		ft_putendl_fd(strs[i++], STDOUT);
	free(strs);
	ft_hashmap_clear(hashmap, &ft_linkhash_clear);
	return (0);
}
