/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:30:03 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/22 17:37:18 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H 

# include <unistd.h>
# include <stddef.h>
# include "stdlib.h"
# include "libft.h"

# define HASHMAP_SIZE 512

char	*get_next_line(int fd);

// linked lists
t_list	*ft_lst_new(t_any content);
void	ft_lstclear(t_list **head, void (*f_free)(t_any));
void	ft_lstdelone(t_list *node, void (*f_free)(t_any));

#endif
