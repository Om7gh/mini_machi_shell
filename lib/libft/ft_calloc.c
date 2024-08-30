/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:26:56 by omghazi           #+#    #+#             */
/*   Updated: 2023/11/20 11:02:29 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	total_case;

	if (count > 0 && SIZE_MAX / count < size)
		return (NULL);
	total_case = count * size;
	ptr = malloc(total_case);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_case);
	return (ptr);
}
