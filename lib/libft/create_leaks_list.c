/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_leaks_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:25:49 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/26 16:03:20 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_propre	*create_addr(void *addr)
{
	t_propre	*new;

	new = (t_propre *)malloc(sizeof(t_propre));
	new->addr = addr;
	new->next = NULL;
	return (new);
}

void	append_address(t_propre **head, void *addr)
{
	t_propre	*new;
	t_propre	*last;

	new = create_addr(addr);
	if (!*head)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
}
