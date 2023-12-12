/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:28:22 by lnicolli          #+#    #+#             */
/*   Updated: 2023/10/30 13:05:06 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*firstnode;
	t_list	*actualnode;

	actualnode = lst;
	firstnode = (t_list *)0;
	if (!lst)
		return ((t_list *)0);
	firstnode = ft_lstnew(f(actualnode->content));
	actualnode = firstnode;
	if (!firstnode)
		return ((t_list *)0);
	lst = lst->next;
	while (lst)
	{
		actualnode->next = ft_lstnew(f(lst->content));
		if (!actualnode->next)
		{
			ft_lstclear(&firstnode, del);
			return ((t_list *)0);
		}
		actualnode = actualnode->next;
		lst = lst->next;
	}
	return (firstnode);
}
