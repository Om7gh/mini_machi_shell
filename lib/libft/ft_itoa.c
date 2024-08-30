/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:55:50 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/26 15:52:38 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_num_len(long long n)
{
	size_t	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static long	get_num_temp(long long n)
{
	long long	tmp;
	int			i;

	tmp = 1;
	i = get_num_len(n);
	while (i > 1)
	{
		tmp *= 10;
		i--;
	}
	return (tmp);
}

static void	check_negative(long long n, char *arr, size_t *i)
{
	if (n < 0)
	{
		arr[*i] = '-';
		(*i)++;
	}
}

static void	insertion(long long temp, char *arr, long long num, size_t *i)
{
	while (temp > 0)
	{
		arr[*i] = (num / temp) + '0';
		num = num % temp;
		temp /= 10;
		(*i)++;
	}
	arr[*i] = '\0';
}

char	*ft_itoa(int n)
{
	long long	num;
	long long	temp;
	char		*arr;
	size_t		i;
	size_t		num_len;

	num = n;
	temp = 1;
	i = 0;
	num_len = get_num_len(num);
	temp = get_num_temp(num);
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		num = -(long long)n;
		num_len++;
	}
	arr = o_malloc(num_len + 1);
	check_negative(n, arr, &i);
	insertion(temp, arr, num, &i);
	return (arr);
}
