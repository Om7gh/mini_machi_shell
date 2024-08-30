/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:13:05 by omghazi           #+#    #+#             */
/*   Updated: 2023/11/15 17:32:32 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	while (s_len > 0 && s[s_len] != (unsigned char)c)
		s_len--;
	if (s[s_len] == (unsigned char)c)
		return ((char *)(s + s_len));
	return (NULL);
}
