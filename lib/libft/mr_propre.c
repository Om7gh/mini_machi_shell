/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_propre.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:15:19 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/29 16:42:39 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	mr_propre(t_propre *prop)
{
	t_propre	*tmp;

	while (prop)
	{
		tmp = prop;
		prop = prop->next;
		free(tmp->addr);
		free(tmp);
	}
}

void	*o_malloc(size_t size)
{
	static t_propre		*propre;
	void				*addr;

	addr = malloc(size);
	if (!addr)
	{
		ft_putstr_fd("malloc error\n", 2);
		mr_propre(propre);
		exit(1);
	}
	append_address(&propre, create_addr(addr));
	return (addr);
}
