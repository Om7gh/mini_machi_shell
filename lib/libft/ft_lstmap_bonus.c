/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:51:01 by omghazi           #+#    #+#             */
/*   Updated: 2023/11/17 13:08:59 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*root;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	root = NULL;
	while (lst)
	{
		tmp = ft_lstnew(NULL);
		if (!tmp)
		{
			ft_lstclear(&root, del);
			return (NULL);
		}
		tmp->content = f(lst->content);
		ft_lstadd_back(&root, tmp);
		lst = lst->next;
	}
	return (root);
}
