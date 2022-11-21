/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:17:33 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/21 19:06:07 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

#define ARRAY_SIZE 2

typedef	struct	s_linked_array
{
	t_list	*array;
	t_list	*last;
	size_t	index;
	size_t	n_array;
}	t_linkarray;

t_list		*ft_lst_new(t_any content);
t_linkarray	*ft_larray_new(t_any *data, size_t n);
void		ft_larray_add(t_linkarray *linkarray, t_any data);
void		ft_larray_free(t_linkarray *linkarray, void (*f_free)(t_any));
