/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 01:34:23 by ylabtaim          #+#    #+#             */
/*   Updated: 2021/11/12 13:03:23 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;

	head = 0;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
			ft_lstdelone(new, del);
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
