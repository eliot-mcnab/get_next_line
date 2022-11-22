/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:09:32 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 11:29:35 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_bonus.h"
#include "libft.h"

int	main(void)
{
	char		**strs;
	t_linkarray	*linkedarray;
	char		**array;
	size_t		i;

	strs = malloc(4 * sizeof(*strs));
	strs[0] = ft_strdup("test");
	strs[1] = ft_strdup("hello");
	strs[2] = ft_strdup("nope");
	strs[3] = ft_strdup("yooo");
	linkedarray = ft_larray_new((t_any *)strs, 4);
	array = (char **)ft_larray_collect(linkedarray);
	i = 0;
	while (array[i])
	{
		ft_putendl_fd(array[i], STDOUT);
		i++;
	}
	free(array);
	ft_larray_free(linkedarray, NULL);
	free(strs);
	return (0);
}
