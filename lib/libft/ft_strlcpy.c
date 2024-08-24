/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:04:31 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/01 20:22:34 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	slen;
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	slen = ft_strlen(src);
	if (len)
	{
		while (*src && ++i < len)
			*dst++ = *src++;
		*dst = 0;
	}
	return (slen);
}
