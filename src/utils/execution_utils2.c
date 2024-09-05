/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:26:01 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/05 16:36:32 by omghazi          ###   ########.fr       */
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
		if (ft_strncmp(tmp->cmd[0], "echo", 4) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "cd", 2) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "pwd", 3) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "export", 6) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "unset", 5) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "env", 3) == 0)
			return (1);
		if (ft_strncmp(tmp->cmd[0], "exit", 4) == 0)
			return (1);
	}
	return (0);
}

int	new_cmd_len(t_cmd *cmd)
{
	int	i;
	int	j;
	t_cmd	*tmp;

	i = 0;
	j = 0;
	tmp = cmd;
	while (tmp->cmd[i])
	{
		if (ft_strlen(tmp->cmd[i]) == 0 && tmp->stat[i] == GENERAL)
		{
			i++;
			continue ;
		}
		i++;
		j++;
	}
	return (j);
}

// t_cmd	*filter_empty_cmd(t_cmd *cmd)
// {
// 	t_cmd	*tmp;
// 	t_cmd	*new;
// 	int		i;
// 	int		j;

// 	printf("%d\n", cmd->cmd_len);
// 	1 && (tmp = cmd, i = 0, j = 0);
// 	new = malloc(sizeof(t_cmd));
// 	new->cmd = malloc(sizeof(char *) * (new_cmd_len(tmp) + 1));
// 	while (tmp->cmd[i])
// 	{
// 		if (tmp->stat[i] == GENERAL && tmp->cmd_len == 0)
// 			i++;
// 		else
// 			new->cmd[j++] = ft_strdup(tmp->cmd[i++]);
// 	}
// 	new->cmd[j] = NULL;
// 	return (new);
// }
