/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 03:35:08 by omghazi           #+#    #+#             */
/*   Updated: 2023/11/20 12:36:45 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_sign(const char **s)
{
	int	sign;

	sign = 1;
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			sign *= -1;
		(*s)++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	long	res;
	long	tmp;
	int		sign;

	res = 0;
	tmp = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = num_sign(&str);
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		if (res < tmp && sign == 1)
			return (-1);
		if (res < tmp && sign == -1)
			return (0);
		tmp = res;
		str++;
	}
	return (sign * res);
}
