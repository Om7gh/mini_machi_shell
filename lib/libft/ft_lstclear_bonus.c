/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:36:53 by omghazi           #+#    #+#             */
/*   Updated: 2023/11/17 16:14:18 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*head;
	t_list	*temp;

	if (!lst || !del)
		return ;
	head = *lst;
	while (head)
	{
		temp = head->next;
		del(head->content);
		free(head);
		head = temp;
	}
	*lst = NULL;
}
