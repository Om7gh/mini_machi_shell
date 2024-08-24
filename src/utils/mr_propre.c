/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_propre.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:15:19 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/22 15:26:12 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	mr_propre(t_propre *prop)
// {
// 	t_propre	*tmp;

// 	while (prop)
// 	{
// 		tmp = prop;
// 		prop = prop->next;
// 		free(tmp->str);
// 		free(tmp);
// 	}
// }

// void	*o_malloc(size_t size, t_propre *prop)
// {
// 	static char	*addr;

// 	addr = malloc(size);
// 	append_addrs(&prop, create_addr(addr));
// 	if (!addr)
// 	{
// 		ft_putstr_fd("malloc error\n", 2);
// 		mr_propre(prop);
// 		exit(1);
// 	}
// 	return (addr);
// }
