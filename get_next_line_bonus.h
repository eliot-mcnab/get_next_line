/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:17:33 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 11:14:47 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "get_next_line.h"

# define ARRAY_SIZE 2

typedef	struct	s_linked_array
{
	t_list	*first;
	t_list	*last;
	size_t	index;
	size_t	n_array;
}	t_linkarray;

typedef struct	s_hashmap
{
	t_list	**map;
	size_t	size;
}	t_hashmap;

// linked array
t_list		*ft_lst_new(t_any content);
t_linkarray	*ft_larray_new(t_any *data, size_t n);
void		ft_larray_add(t_linkarray *linkarray, t_any data);
void		ft_larray_free(t_linkarray *linkarray, void (*f_free)(t_any));
t_any		*ft_larray_collect(t_linkarray *linkarray);

// fixed-size hashmaps
t_hashmap	*ft_hashmap_fd(size_t size);
void		ft_hashmap_add(t_hashmap *hashmap, size_t hash, t_any *data);
t_any		ft_hashmap_get(t_hashmap *hashmap, size_t hash);
void		ft_hashmap_clear(t_hashmap *hashmap, void (*f_free)(t_any));

#endif
