/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 09:42:00 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/26 16:43:24 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execution(t_minishell *mini, t_cmd *cmds)
{
	if (node_len(cmds) == 1)
		return (single_process(mini, cmds));
	else
	{
		mini->pipe = o_malloc(sizeof(int *) * node_len(cmds) - 1);
		if (!mini->pipe)
			return (1);
		return (multi_process(mini, cmds));
	}
	return (mini->ret_value);
}
