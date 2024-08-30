/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:33:08 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/26 11:55:18 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	if (!s1 || !s2)
		return (0);
	while ((*s1 && *s2) && (*s1 == *s2) && n--)
	{
		s1++;
		s2++;
	}
	return (((unsigned char)(*s1) - (unsigned char)(*s2)) * (n != 0));
}
