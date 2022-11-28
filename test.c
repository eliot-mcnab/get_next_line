/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:15:31 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/28 10:33:48 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	FILE	*fp;
	int		fd;
	char	*line;

	fp = fopen("test.txt", "r");
	fd = fileno(fp);
	line = get_next_line(fd);
	printf("%s\n", line);
	/* printf("======\n");
	line = get_next_line(fd);
	printf("%s\n", line); */
	return (0);
}
