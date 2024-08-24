/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:24 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 18:01:30 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid(char c)
{
	return (c == '+' || c == '-' || c == ' ' || c == '|' || c == '\t'
		|| c == '>' || c == '<' || (c > '0' && c <= '9'));
}

int	ft_exit(t_cmd *cmd, t_minishell *mini)
{
	int	res;
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	if (!cmd->cmd[1])
		exit(mini->ret_value);
	while (cmd->cmd[i])
	{
		j = 0;
		if (i > 1)
		{
			ft_putendl_fd("exit", 2);
			ft_putstr_fd("Minishell : exit: too many arguments\n", 2);
			return (1);
		}
		while (cmd->cmd[i][j])
		{
			if (!is_valid(cmd->cmd[i][j]))
			{
				flag = 1;
				break ;
			}
			j++;
		}
		if (flag)
			break ;
		i++;
	}
	if (flag)
	{
		ft_putstr_fd("Minishell : exit: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	res = ft_atoi(cmd->cmd[1]);
	if (res < 0)
		res = 256 + res;
	exit(res);
	return (0);
}
