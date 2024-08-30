/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:51:24 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/29 16:38:42 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (!dst && size == 0)
		return (src_len);
	dest_len = ft_strlen(dst);
	if (!src)
		return (dest_len);
	if (dest_len >= size)
		return (size + src_len);
	i = 0;
	while (src[i] && (i + dest_len) < size - 1)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = 0;
	return (dest_len + src_len);
}
