/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:24 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/29 18:33:49 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid(char c)
{
	return (c == '+' || c == '-' || c == 32 || c == '\t' \
		|| (c >= '0' && c <= '9'));
}

int	check_multi_args(t_cmd *cmd, int *flag)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->cmd[++i])
	{
		j = -1;
		if (i > 1)
		{
			ft_putendl_fd("exit", 2);
			ft_putstr_fd("Minishell : exit: too many arguments\n", 2);
			return (0);
		}
		while (cmd->cmd[i][++j])
		{
			if (!is_valid(cmd->cmd[i][j]))
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
	res = ft_atoi(cmd->cmd[1]);
	if (res < 0)
		res = 256 + res;
	(ft_putendl_fd("exit", 1), exit(res));
	return (0);
}
