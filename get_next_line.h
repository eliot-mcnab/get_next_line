/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:44:25 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/25 18:15:54 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdbool.h>

typedef struct	s_magic
{
	unsigned long int	lomagic;
	unsigned long int	himagic;
	unsigned long int	crmagic;
}	t_magic;

typedef unsigned long int	t_longword;

char	*ft_quickfind(char *str, int c);

#endif
