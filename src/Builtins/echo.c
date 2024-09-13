/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/13 11:22:45 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**check_args(char **cmd, int *count)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		j = 2;
		if (cmd[i][0] == '-' && cmd[i][1] == 'n')
		{
			while (cmd[i][j] && cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] != '\0')
				return (&cmd[i]);
			else
			{
				(*count)++;
				i++;
				continue ;
			}
		}
		else
			return (&cmd[i]);
	}
	return (NULL);
}

int	echo(t_cmd *cmd)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	args = check_args(cmd->cmd, &i);
	j = 0;
	if (args)
	{
		while (args[j])
		{
			ft_putstr_fd(args[j], 1);
			if (args[j + 1])
				ft_putstr_fd(" ", 1);
			j++;
		}
		if (!i)
			ft_putstr_fd("\n", 1);
	}
	return (0);
}
