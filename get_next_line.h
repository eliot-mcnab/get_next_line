/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:44:25 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/30 17:33:39 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define ARRAY_SIZE 32

// _Pragma("GCC diagnostic push")
// _Pragma("GCC diagnostic ignored \"-Wpadded\"")

typedef struct s_line
{
	size_t	i;
	bool	end;
	char	buffer[BUFFER_SIZE + 1];
	int		fd;
}	t_line;

// _Pragma("GCC diagnostic pop")

typedef struct s_magic
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

#endif
