/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:45:32 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/30 17:33:19 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * @brief Reads BUFFER_SIZE bytes from the file described by [fd] into [buffer].
 *	guarantees to null-terminate [buffer] after the last read character.\
 *
 * @param fd (int): file descriptor of the file to read.
 * @param line (t_line *): pointer to the line structure used by get_next_line.
 *
 * @return (ssize_t): the numbers of characters read into [buffer].
 */
static ssize_t	saferead(int fd, t_line *line)
{
	ssize_t	i;

	if (BUFFER_SIZE < 1)
		return (0);
	i = read(fd, line->buffer, BUFFER_SIZE);
	line->buffer[i] = '\0';
	if (!i)
		line->i = 0;
	return (i);
}

/*
 * @brief Copies the contents of a string between [str_start] and [str_end].
 * 	If [str_end] [str_start] then no bytes will be copied. At most [str_end] - 
 * 	[str_start] bytes will be copied, but if the terminating null byte in 
 * 	[str_start] is before [str_end], copy will stop there.
 *
 * @param str_start (char *): the start of the string to copy.
 * @param str_end (char *): the end of the string to copy. 
 *
 * @return (char *): the substring in [str_start] between [str_start] and
 * 	[str_end].
 */
static char	*ft_substr(char *str_start, char *str_end)
{
	char	*strcpy;
	size_t	i;

	if (str_start > str_end)
		return (NULL);
	strcpy = malloc((size_t)(str_end - str_start + 1) * sizeof(*strcpy));
	if (!strcpy)
		return (NULL);
	i = 0;
	while (str_start[i] && str_start + i < str_end)
	{
		strcpy[i] = str_start[i];
		i++;
	}
	strcpy[i] = '\0';
	return (strcpy);
}

/*
 * @brief Joins two substrings into one string and frees the original strings.
 * @warning Do not use if [str_a] or [str_b] are on the statck.
 *
 * @param str_a (char *): string to prepend.
 * @param str_b (char *): string to append.
 *
 * @return (char *): result of joining [str_a] and [str_b].
 */
static char	*ft_freejoin(char *str_a, char *str_b)
{
	size_t	len_tot;
	size_t	i;
	size_t	j;
	char	*joined;

	len_tot = ft_quicklen(str_a) + ft_quicklen(str_b);
	i = 0;
	j = 0;
	joined = malloc((len_tot + 1) * sizeof(*joined));
	if (!joined)
		return (NULL);
	while (str_a && str_a[j])
		joined[i++] = str_a[j++];
	j = 0;
	while (str_b && str_b[j])
		joined[i++] = str_b[j++];
	if (str_a)
		free(str_a);
	if (str_b)
		free(str_b);
	joined[i] = '\0';
	return (joined);
}

/*
 * @brief Copies all characters in the buffer up to the end of the current line
 * 	and appends them to the current line read so far. If buffer does not contain
 * 	the end of the line, appends the entire buffer.
 *
 * @param line (t_line *): pointer to the line structure used by get_next_line.
 * @param line_current (char *): the current line read so far.
 *
 * @return (char *): the current line read so far.
 */
static char	*ft_to_line_end(t_line *line, char *line_current)
{
	char	*line_end;
	char	*line_new;

	line_end = ft_quickfind(line->buffer + line->i, '\n');
	if (*line_end == '\n')
	{
		line_new = ft_substr(line->buffer + line->i, &line_end[1]);
		line->end = true;
	}
	else
		line_new = ft_substr(line->buffer + line->i, line_end);
	if (!line_new)
		return (NULL);
	if (BUFFER_SIZE > 0)
		line->i = (size_t)(line_end - line->buffer) % (BUFFER_SIZE);
	return (ft_freejoin(line_current, line_new));
}

/*
 * @brief Gets the next line in the file corresponding to the given file 
 * 	directory [fd]. Starts at the beggining of the file and returns the 
 * 	following line on each successive function call. Currently only handles one
 * 	file at a time.
 *
 * @param fd (int): file directory of the file to read. Must point to a file
 * 	wich was opened with read permissions enabled.
 *
 * @return (char *): the next line in the file corresponding to [fd].
 */
char	*get_next_line(int fd)
{
	static t_line	line = {.i = 0, .fd = -1};
	char			*line_current;

	line_current = NULL;
	line.end = false;
	line.i = (line.i * (line.fd == fd)) % (BUFFER_SIZE + (BUFFER_SIZE == 0));
	line.fd = fd;
	while (!line.end)
	{
		if (!line.i && (saferead(fd, &line) < 0))
		{
			free(line_current);
			return (NULL);
		}
		if (!line.buffer[line.i])
			return (line_current);
		line_current = ft_to_line_end(&line, line_current);
		if (!line_current)
			return (NULL);
	}
	line.i += BUFFER_SIZE > 1;
	return (line_current);
}
