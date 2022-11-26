/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:35:39 by emcnab            #+#    #+#             */
/*   Updated: 2022/11/26 15:56:22 by emcnab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "get_next_line.h"
# include "libft.h"

/* typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list; */

typedef struct s_linkstr
{
	t_list	*strs_first;
	t_list	*strs_last;
	size_t	linksize;
	size_t	i;
}	t_linkstr;

// linked lists
t_list	*ft_lst_new(void *content);
void	ft_lst_delone(t_list *lst, void (*f_free)(void *));
void	ft_lst_delall(t_list **lst, void (*f_free)(void *));

// linked strings
t_linkstr	*ft_linkstr_new(size_t linksize);
void		ft_linkstr_add(t_linkstr *linkstr, char *str);
char		*ft_linkstr_collect(t_linkstr *linkstr);
void		ft_linkstr_delall(t_linkstr *linkstr);

#endif
