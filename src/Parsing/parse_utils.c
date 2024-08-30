/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:35:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/30 16:01:51 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_special(int c)
{
	return (c == '|' || c == '>' || c == '<' || c == ' ' || \
		c == '"' || c == '\'');
}

void	init_counters(int *index, int *count)
{
	index[0] = 0;
	index[1] = 0;
	count[0] = 0;
	count[1] = 0;
}

void	handle_word_token(t_tokenizer *tmp, t_cmd *new, int *i)
{
	if (ft_strchr(tmp->token, ' ') && *tmp->stat == GENERAL)
	{
		new->cmd[(*i)++] = ft_split(ft_strdup(tmp->token), ' ')[0];
		new->cmd[(*i)++] = ft_split(ft_strdup(tmp->token), ' ')[1];
	}
	else
		new->cmd[(*i)++] = ft_strdup(tmp->token);
}

void	handle_non_word_token(t_tokenizer **tmp, t_cmd *new, int *j)
{
	new->red[(*j)++] = ft_strdup((*tmp)->token);
	new->red[(*j)++] = ft_strdup((*tmp)->next->token);
	*tmp = (*tmp)->next;
}

void	send_to_execution(t_tokenizer *token, t_cmd **cmd)
{
	t_cmd		*new;
	t_tokenizer	*tmp;
	int			index[2];
	int			count[2];

	tmp = token;
	while (tmp)
	{
		init_counters(index, count);
		count_len(tmp, &count[0], &count[1]);
		if (ft_strchr(tmp->token, ' ') && *tmp->stat == GENERAL)
			count[0] += 1;
		new = new_cmd(count[0], count[1]);
		while (tmp && *tmp->type != PIPE)
		{
			if (*tmp->type == WORD)
				handle_word_token(tmp, new, &index[0]);
			else
				handle_non_word_token(&tmp, new, &index[1]);
			tmp = tmp->next;
		}
		append_to_exec(cmd, new);
		if (tmp && tmp->next)
			tmp = tmp->next;
	}
}
