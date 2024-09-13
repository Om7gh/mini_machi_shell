/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:26:01 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/13 11:26:29 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtins(t_cmd *cmds)
{
	t_cmd	*tmp;

	if (!cmds)
		return (0);
	tmp = cmds;
	if (tmp)
	{
		if (ft_strncmp(tmp->cmd[0], "echo", 5) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "cd", 3) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "pwd", 4) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "export", 7) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "unset", 6) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "env", 4) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "exit", 5) == 0)
			return (1);
	}
	return (0);
}
