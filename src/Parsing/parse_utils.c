/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:35:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/30 15:34:58 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_special(int c)
{
	return (c == '|' || c == '>' || c == '<' || c == ' ' || \
		c == '"' || c == '\'');
}

void	send_to_execution(t_tokenizer *token, t_cmd **cmd)
{
	t_cmd		*new;
	int			i;
	int			j;
	t_tokenizer	*tmp;
	int			count[2];

	tmp = token;
	while (tmp)
	{
		1 && (i = 0, j = 0, count[0] = 0, count[1] = 0);
		count_len(tmp, &count[0], &count[1]);
		new = new_cmd(count[0], count[1]);
		while (tmp && *tmp->type != PIPE)
		{
			if (*tmp->type == WORD)
			{
				if (ft_strchr(tmp->token, ' ') && *tmp->stat == GENERAL)
				{
					new = new_cmd(count[0] + 1, count[1]);
					new->cmd[i] = ft_split(ft_strdup(tmp->token), ' ')[0];
					i++;
					new->cmd[i] = ft_split(ft_strdup(tmp->token), ' ')[1];
					i++;
				}
				else
					new->cmd[i++] = ft_strdup(tmp->token);
			}
			else if (*tmp->type != WORD)
			{
				new->red[j++] = ft_strdup(tmp->token);
				new->red[j++] = ft_strdup(tmp->next->token);
				tmp = tmp->next;
			}
			tmp = tmp->next;
		}
		append_to_exec(cmd, new);
		if (tmp && tmp->next)
			tmp = tmp->next;
	}
}
