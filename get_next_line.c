/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:45:32 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/28 10:38:53 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_line	line = {0, };
	char			*line_end;
	char			*line_current;
	t_linkstr		*linkstr;
	char			*substr;

	line_current = NULL;
	line_end = "_";
	linkstr = ft_linkstr_new(ARRAY_SIZE);
	while (*line_end != '\n')
	{
		line.buffer[BUFFER_SIZE] = '\0';
		if (!line.i)
			read(fd, line.buffer, BUFFER_SIZE);
		line_end = ft_quickfind(line.buffer, '\n');
		substr = ft_substr(line.buffer + line.i, line_end);
		line.i = (size_t)((line.i + line_end - line.buffer) % BUFFER_SIZE);
		ft_linkstr_add(linkstr, substr);
		if (*line_end == '\n')
		{
			line_current = ft_linkstr_collect(linkstr);
			ft_linkstr_delall(linkstr);
		}
	}
	return (line_current);
}

char	*ft_stralloc(size_t size)
{
	char	*str;

	str = malloc((size + 1) * sizeof(*str));
	if (!str)
		return (NULL);
	str[size] = '\0';
	return (str);
}

char	*ft_substr(char *str_start, char *str_end)
{
	char	*strcpy;
	size_t	i;

	if (str_start > str_end)
		return (NULL);
	strcpy = ft_stralloc((size_t)(str_end - str_start));
	if (!strcpy)
		return (NULL);
	i = 0;
	while (str_start + i < str_end)
	{
		strcpy[i] = str_start[i];
		i++;
	}
	return (strcpy);
}
