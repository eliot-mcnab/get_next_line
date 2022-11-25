/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:47:28 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/25 19:22:34 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static t_magic	ft_magic(int c)
{
	t_magic	magic;
	size_t	i;

	magic.lomagic = 0x01L;
	magic.himagic = 0x80L;
	magic.crmagic = (t_longword) c;
	i = 1;
	while (i < sizeof(t_longword))
	{
		magic.lomagic = (magic.lomagic << i * 8) | magic.lomagic;
		magic.himagic = (magic.himagic << i * 8) | magic.himagic;
		magic.crmagic = (magic.crmagic << i * 8) | magic.crmagic;
		i *= 2;
	}
	magic.crmagic = ~magic.crmagic;
	return (magic);
}

static bool	ft_bytesearch(t_longword lword, t_magic magic)
{
	if ((lword - magic.lomagic) & ~lword & magic.himagic)
		return (true);
	lword &= magic.crmagic;
	if ((lword - magic.lomagic) & ~lword & magic.himagic)
		return (true);
	return (false);
}

static char	*ft_longword_search(t_longword *lword, t_magic magic, int c)
{
	char	*str;
	size_t	j;

	while (true)
	{	
		if (!ft_bytesearch(*lword++, magic))
			continue ;
		str = (char *)(lword - 1);
		j = 0;
		while (j < sizeof(t_longword))
		{
			if (!str[j] || str[j] == c)
				return (str + j);
			j++;
		}
	}
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wcast-align\"")

char	*ft_quickfind(char *str, int c)
{
	t_magic		magic;
	t_longword	*lword;
	size_t		i;

	c = (unsigned char) c;
	i = 0;
	while (((t_longword)(str + i) & (sizeof(t_longword) - 1)))
	{
		if (!str[i] || str[i] == c)
			return (str + i);
		i++;
	}
	magic = ft_magic(c);
	lword = (t_longword *)(str + i * sizeof(*str));
	return (ft_longword_search(lword, magic, c));
}

_Pragma("GCC diagnostic pop")
