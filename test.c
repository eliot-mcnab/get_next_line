/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:09:32 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 16:02:02 by emcnab           ###   ########.fr       */
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
	char		**strs;
	t_linkarray	*linkarray;
	t_hashmap	*hashmap;
	char		**array;
	size_t		i;

	strs = malloc(4 * sizeof(*strs));
	strs[0] = ft_strdup("test");
	strs[1] = ft_strdup("hello");
	strs[2] = ft_strdup("nope");
	strs[3] = ft_strdup("yoooo");
	linkarray = ft_larray_new((t_any *)strs, 4);
	hashmap = ft_hashmap_new(32);
	ft_hashmap_set(hashmap, 0, linkarray);
	linkarray = (t_linkarray *)ft_hashmap_get(hashmap, 0);
	array = (char **)ft_larray_collect(linkarray);
	i = 0;
	while (array[i])
		ft_putendl_fd(array[i++], STDOUT);
	free(array);
	free(strs);
	ft_hashmap_clear(hashmap, &ft_linkhash_clear);
	return (0);
}
