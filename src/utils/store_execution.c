/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:44:36 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/05 16:30:40 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	append_to_exec(t_cmd **cmds, t_cmd *cmd)
{
	t_cmd	*head;

	if (!cmds || !cmd)
		return ;
	if (!*cmds)
	{
		*cmds = cmd;
		return ;
	}
	head = *cmds;
	while (head->next)
		head = head->next;
	head->next = cmd;
}

t_cmd	*new_cmd(int cmd, int red, t_stat *stat, int len)
{
	t_cmd	*new;

	new = o_malloc(sizeof(t_cmd));
	new->cmd = o_malloc(sizeof(char *) * (cmd + 1));
	new->red = o_malloc(sizeof(char *) * (red + 1));
	new->cmd[cmd] = NULL;
	new->red[red] = NULL;
	new->stat = malloc(sizeof(t_stat));
	new->stat = stat;
	new->cmd_len = len;
	new->next = NULL;
	return (new);
}

void	del_one_cmd(t_cmd *cmds, void (*del)(void *))
{
	if (!cmds)
		return ;
	del(cmds->red);
	del(cmds->cmd);
	free(cmds);
}

void	clear_cmd(t_cmd **cmd, void (*del)(void *))
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		del_one_cmd(*cmd, del);
		*cmd = tmp;
	}
}
