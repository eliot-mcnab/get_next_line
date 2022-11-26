/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:15:31 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/26 15:45:38 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "get_next_line_bonus.h"
#include <stdio.h>

#define STR_SIZE 32

int	main(void)
{
	t_linkstr	*linkstr;
	char		*collect;

	linkstr = ft_linkstr_new(STR_SIZE);
	ft_linkstr_add(linkstr, "test");
	ft_linkstr_add(linkstr, "hello");
	ft_linkstr_add(linkstr, "world");
	collect = ft_linkstr_collect(linkstr);
	ft_putstr_fd(collect, STDOUT);
	ft_linkstr_delall(linkstr, &free);
	free(collect);
	return (0);
}
