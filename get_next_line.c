/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:30:30 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/25 15:11:53 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_bonus.h"
#include <stdbool.h>

#define LOMAGIC_4 0x01010101L
#define HIMAGIC_4 0x80808080L
#define LOMAGIC_8 0x0101010101010101L
#define HIMAGIC_8 0x8080808080808080L

/* char	*get_next_line(int fd)
{
	static t_hashmap	*hashmap = NULL;
	t_any				buffer;

	if (!hashmap)
		hashmap = ft_hashmap_new(HASHMAP_SIZE);
	if (!ft_hashmap_get(hashmap, fd))
		ft_hashmap_set(hashmap, fd, ft_larray_new(ARRAY_SIZE));
} */

/*
 * @brief Searches for the character [c] in the longword pointed to by [lword]
 * 	by comparing up to 8 bytes at a time. Works on architectures with 32-bit 
 * 	and 64-bit longwords.
 *
 * @param lword (t_longword): the longword to search.
 * @param c (int): the character to find in [lword].
 *
 * @return (bool): true if [c] was found in [lword] or the end of the string
 * 	represented by [lword] was reached, false otherwise.
 */
static bool	ft_bytesearch(t_longword lword, int c)
{
	size_t		lsize;
	size_t		i;
	t_longword	lc;
	bool		found;

	found = false;
	lsize = sizeof(lword);
	if (lsize > 4 && (lword - LOMAGIC_8) & ~lword & HIMAGIC_8)
		found = true;
	else if ((lword - LOMAGIC_4) & ~lword & HIMAGIC_4)
		found = true;
	i = 1;
	lc = c;
	while (i <= lsize)
	{
		lc = (lc << i * 8) | lc;
		i++;
	}
	lword &= ~lc;
	if (lsize > 4 && (lword - LOMAGIC_8) & ~lword & HIMAGIC_8)
		found = true;
	else if ((lword - LOMAGIC_4) & ~lword & HIMAGIC_4)
		found = true;
	return (found);
}

/*
 * @brief Optimised linear search for a character [c] in a string [str]. Takes
 * 	advantage of longwords to compare up to 8 bytes at a time. Only works on
 * 	architectures with 32-bit and 64-bit longwords.
 *
 * @param str (t_str): the string to search.
 * @param c (int): the character to find, considered as an unsigned char.
 *
 * @return (char *): pointer to the first occurrence of [c] in [str], or to the
 * 	terminating null-byte in [str] if [c] was not found.
 */
char	*ft_quickfind(t_str str, int c)
{
	t_longword	*lword_ptr;
	t_longword	lword;
	size_t		i;

	c = (unsigned char) c;
	while ((t_longword)str & (sizeof(lword) - 1))
	{
		if (!*str || *str == c)
			return ((char *)str);
		str++;
	}
	lword_ptr = (t_longword *)str;
	while (true)
	{
		lword = *lword_ptr++;
		if (!ft_bytesearch(lword, c))
			continue ;
		i = 0;
		str = (t_str)(lword_ptr - 1);
		while (i++ < sizeof(lword))
			if (!str[i - 1] || str[i - 1] == c)
				return ((char *)str + i - 1);
	}
}
