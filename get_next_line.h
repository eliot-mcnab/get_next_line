/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:44:25 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/28 14:55:38 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>

# define BUFFER_SIZE 1
# define ARRAY_SIZE 32

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wpadded\"")

typedef struct	s_line
{
	size_t	i;
	char	buffer[BUFFER_SIZE + 1];
}	t_line;

_Pragma("GCC diagnostic pop")

typedef struct	s_magic
{
	unsigned long int	lomagic;
	unsigned long int	himagic;
	unsigned long int	crmagic;
}	t_magic;

typedef unsigned long int	t_longword;

char	*get_next_line(int fd);

// strings
char	*ft_quickfind(char *str, int c);
size_t	ft_quicklen(char *str);
char	*ft_stralloc(size_t size);
char	*ft_substr(char *str_start, char *str_end);

#endif
