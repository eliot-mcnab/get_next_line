/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:47:28 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/29 16:29:53 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

/*
 * @brief Generates the longwords used in bitwise operations to find the byte
 * 	[c].
 *
 * @param c (int): the byte to search for.
 * 
 * @return (t_magic): structure containing al the longwords needed to find [c].
 * @see ft_bytesearch(2)
 */
static t_magic	ft_magic(unsigned char c)
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

/*
 * @brief Searches for a byte in a longword [lword] using bitwise operations
 * 	with the longwords stored in [magic].
 * 
 * Let us suppose the current C implementation supports 32bit longwords, but
 * this algorithm will function for any longword size.
 *
 * --------------------------- [ STARTING BYTES ] ----------------------------
 *
 * bits :	10010011 01001000 00000000 00110010
 * bytes:	AAAAAAAA BBBBBBBB CCCCCCCC DDDDDDDD
 *       	         ^^^^^^^^
 * we are looking for value Ox48 located in byte B.
 *
 * ----------------------------- [ MAGIC BYTES ] -----------------------------
 *
 * lomagic:	00000001 00000001 00000001 00000001
 * himagic: 10000000 10000000 10000000 10000000
 * crmagic: 10110111 10110111 10110111 10110111
 *
 * notice that crmagic is made up of the binary one complement to the value we 
 * are looking for (0x48).
 *
 * -------------------------- [ BITWISE OPERATIONS ] -------------------------
 *
 * step 1: lword & crmagic
 *  -> this has the effect of nullifying ONLY the bytes which were equal to
 *  	0x48. Notice that previous 0x0 bytes are now considered the same as
 *  	0x48: this allows us to look for a specific byte while still checking
 *  	for null-bytes at the end of a string.
 * result:	10010011 00000000 00000000 00110010
 *
 * step 2: lword - lomagic
 *  -> removes all first bits in every bytes and propagates the result to the
 *  	left. This has the effect of rolling arounf all 0x0 bytes to 0xFF.
 *  	Importantly, now all 0x0 bytes in step 1 have a valid 8th bit. This will
 *  	be taken advantage of to detect the bytes we are looking for.
 *  result:	10010001 11111110 11111111 00110001
 *
 * step 3: lword & ~lword_initial
 *  -> in step 2 we cannot use the 8th bit of each byte to detect the bytes we
 *  	are looking for, because these are also present in bytes we are not
 *  	interesed in. Note that the bytes we are interested in (byte B and C)
 *  	did not initially have a valid 8th bit, whereas other bytes did. So by
 *  	performing a binary AND with the complement to the initial lword we can
 *  	remove most eroneous 8th bits and only keep those in the bytes we are
 *  	looking for.
 *  result:	00000000 10110110 11111111 00000001
 *
 * step 4: lword & himagic
 *  -> keeps only the bytes with a valid 8th bit. Because of the manipulations
 *  	in step 3, this mostly includes only the bytes we are interested in,
 *  	although there might be some cases wher bytes we are not interested in
 *  	still have a valid 8th byte if they gained one as a result of step 1 &
 *  	2. Notice that the result of this operation with not be 0x0 ONLY IF
 *  	there were bytes with a valid 8th bit, aka: the return of this fucntion
 *  	will be true only if there is a higher than 0 probability that the byte
 *  	we were looking for was contained in [lword].
 *  result:	00000000 10000000 10000000 00000000
 *
 * @param lword (t_longword) : the longword to search.
 * @param magic (t_magic): structure of longwords used to find the byte we are
 * 	looking for.
 *
 * @return (bool): true if the byte we are looking for is POTENTIALLY located in
 * 	[lword], false if there is no probability that the byte we are loking for is
 * 	in [lword].
 */
static bool	ft_bytesearch(t_longword lword, t_magic magic)
{
	lword &= magic.crmagic;
	if ((lword - magic.lomagic) & ~lword & magic.himagic)
		return (true);
	return (false);
}

/*
 * @brief Handles searching for byte [c] in longword [lword] once the string
 * 	pointed to by [lword] has been aligned to the size of longwords in the
 * 	current c implementation.
 *
 * @param lword (t_longword *): longword pointer to the string being searched in
 * 	ft_quickfind.
 * @param magic (t_magic): strucutre of longwords needed for the bitwise
 * 	operations required to find [c].
 * @param c (int): the byte to find in [lword].
 *
 * @return (char *): pointer to the first byte to match [c] or the end of the
 * 	string pointed to by [lword] if [c] was not found.
 */
static char	*ft_longword_search(t_longword *lword, t_magic magic,
	unsigned char c)
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

// _Pragma("GCC diagnostic push")
// _Pragma("GCC diagnostic ignored \"-Wcast-align\"")

/*
 * @brief Rapidly searches for a character [c] in a string [str]. Takes
 * 	advantage of longwords to compare as many bytes as possible. Support any
 * 	c longbyte implementation.
 *
 * 	Searching is done by first aligning [str] to the size of a longword in the
 * 	current C implementation and then searching for [c] one longword at a time
 * 	instead of one byte at a time. Since c standard defines long as containing
 * 	at least 32 bits, or 4 bytes, this approach is at least 4x as fast as 
 * 	standard linear search. On implementations which support 64bit or more 
 * 	longwords, this increase is even more noticeable.
 *
 * @param str (char *): the string to search.
 * @param c (int): the character to find, considered as an unsigned char.
 *
 * @return (char *): pointer to the first occurenceof [c] in [str], or to the
 * 	terminating null-byte at the end of [str] if [c] was not found.
 */
char	*ft_quickfind(char *str, int c)
{
	t_magic		magic;
	t_longword	*lword;
	size_t		i;

	if (!str)
		return (0);
	i = 0;
	while (((t_longword)(str + i) & (sizeof(t_longword) - 1)))
	{
		if (!str[i] || str[i] == c)
			return (str + i);
		i++;
	}
	magic = ft_magic((unsigned char)c);
	lword = (t_longword *)(str + i * sizeof(*str));
	return (ft_longword_search(lword, magic, (unsigned char)c));
}

// _Pragma("GCC diagnostic pop")

/*
 * @brief Determines the length of a null-terminated string [str].
 *
 * @param str (char *): the string to get the length of.
 *
 * @return (size_t): the length of the string [str].
 */
size_t	ft_quicklen(char *str)
{
	return ((size_t)(ft_quickfind(str, '\0') - str));
}
