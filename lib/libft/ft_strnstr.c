/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:36:01 by omghazi           #+#    #+#             */
/*   Updated: 2023/11/16 17:58:53 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	size;

	if (!haystack && !len)
		return (NULL);
	size = ft_strlen(needle);
	if (size == 0)
		return ((char *)haystack);
	while (*haystack && len >= size)
	{
		if ((*haystack == *needle) && ft_strncmp(haystack, needle, size) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
