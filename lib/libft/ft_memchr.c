/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:35:32 by omghazi           #+#    #+#             */
/*   Updated: 2023/11/15 18:35:41 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *s, int c, size_t n)
{
	unsigned char	*memoir;

	memoir = (unsigned char *)s;
	while (n--)
	{
		if (*memoir == (unsigned char)c)
			return (memoir);
		memoir++;
	}
	return (NULL);
}
