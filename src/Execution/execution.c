/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 09:42:00 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 17:41:12 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execution(t_minishell *mini, t_cmd *cmds)
{
	if (node_len(cmds) == 1)
		return (single_process(mini, cmds));
	else
	{
		if (!ft_strncmp(cmds->cmd[0], "./minishell", 11)
			&& !ft_strncmp(cmds->next->cmd[0], "./minishell", 11))
			return (ft_putendl_fd("tty is required", 2), 1);
		mini->pipe = (int **)malloc(sizeof(int *) * node_len(cmds) - 1);
		if (!mini->pipe)
			return (1);
		return (multi_process(mini, cmds));
	}
	return (mini->ret_value);
}
