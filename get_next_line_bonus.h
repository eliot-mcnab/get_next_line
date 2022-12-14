/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:17:33 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 19:05:23 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "get_next_line.h"

typedef struct s_linked_array
{
	size_t	i;
	size_t	array_count;
	size_t	array_size;
	t_list	*first;
	t_list	*last;
}	t_linkarray;

typedef struct s_hashmap
{
	size_t	size;
	t_list	**map;
}	t_hashmap;

typedef struct s_hashdata
{
	size_t	hash;
	t_any	data;
}	t_hashdata;

// linked array
t_linkarray	*ft_larray_new(size_t size);
void		ft_larray_add(t_linkarray *linkarray, t_any data);
void		ft_larray_clear(t_linkarray *linkarray, void (*f_free)(t_any));
t_any		*ft_larray_collect(t_linkarray *linkarray);

// fixed-size hashmaps
t_hashmap	*ft_hashmap_new(size_t size);
void		ft_hashmap_set(t_hashmap *hashmap, size_t hash, t_any data);
t_any		*ft_hashmap_get(t_hashmap *hashmap, size_t hash);
void		ft_hashmap_clear(t_hashmap *hashmap, void (*f_free)(t_any));

#endif
