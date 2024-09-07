/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:24 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/07 17:00:29 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_atoi_exit(const char *str)
{
	long	res;
	long	tmp;
	int		sign;
	int		flag;

	1 && (res = 0, tmp = 0, flag = 0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '\0')
		return (printf("numerique arguement require\n"), INT_MIN);
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
	if (!flag)
		return (printf("exit\nnumerique arguement require\n"), INT_MIN);
	return (sign * res);
}

int	is_valid(char c)
{
	return (c == '+' || c == '-' || (c >= '0' && c <= '9'));
}

int	ft_exit_error()
{
	ft_putendl_fd("exit", 2);
	ft_putendl_fd("Minishell : exit: too many arguments", 2);
	return (0);
}

int	check_multi_args(t_cmd *cmd, int *flag)
{
	int	i;
	int	j;
	int	k;

	1 && (i = 0);
	while (cmd->cmd[++i])
	{
		1 && (k = 0, j = -1);
		if (i > 1)
			return (ft_exit_error());
		while (cmd->cmd[i][++j])
		{
			if (!is_valid(cmd->cmd[i][j]))
				return (*flag = 1, 1);
			if (k++ > 1)
				return (*flag = 1, 1);
		}
	}
	return (-1);
}

int	ft_exit(t_cmd *cmd, t_minishell *mini)
{
	int	res;
	int	flag;

	flag = 0;
	if (!cmd->cmd[1])
		(ft_putendl_fd("exit", 1), exit(mini->ret_value));
	if (!check_multi_args(cmd, &flag))
		return (1);
	if (flag)
	{
		ft_putstr_fd("Minishell : exit: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		(ft_putendl_fd("exit", 2), exit(255));
	}
	res = ft_atoi_exit(cmd->cmd[1]);
	if (res == INT_MIN)
		exit(255);
	if (res == -1)
		res = 256 + res;
	(ft_putendl_fd("exit", 1), exit(res));
	return (0);
}
