/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 05:19:16 by omghazi           #+#    #+#             */
/*   Updated: 2023/11/15 14:40:18 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*destination;
	unsigned char	*source;

	if (dst == src)
		return (dst);
	destination = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dst > src + len || dst <= src)
	{
		while (len--)
			*destination++ = *source++;
	}
	else
	{
		while (len--)
			destination[len] = source[len];
	}
	return (dst);
}
