/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:30:30 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 17:49:24 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_hashmap	*hashmap = NULL;
	t_any				buffer;

	if (!hashmap)
		hashmap = ft_hashmap_new(HASHMAP_SIZE);
	if (!ft_hashmap_get(hashmap, fd))
		ft_hashmap_set(hashmap, fd);
}
