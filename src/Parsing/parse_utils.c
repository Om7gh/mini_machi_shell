/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:35:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/05 18:19:11 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_counters(int *index, int *count)
{
	index[0] = 0;
	index[1] = 0;
	count[0] = 0;
	count[1] = 0;
}

int	ft_split_len(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	handle_word_token(t_tokenizer *tmp, t_cmd *new, int *i)
{
	char	**s;
	int		j;

	j = 0;
	s = NULL;
	if (ft_strchr(tmp->token, ' ') && *tmp->stat == GENERAL)
	{
		s = ft_split(tmp->token, ' ');
		while (s && s[j])
			new->cmd[(*i)++] = ft_strdup(s[j++]);
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
			count[0] = ft_split_len(ft_split(tmp->token, ' '));
		new = new_cmd(count[0], count[1], tmp->stat, ft_strlen(tmp->token));
		while (tmp && *tmp->type != PIPE)
		{
			if (tmp && *tmp->stat == GENERAL && ft_strlen(tmp->token) == 0)
				tmp = tmp->next;
			else
			{
				if (*tmp->type == WORD)
					handle_word_token(tmp, new, &index[0]);
				else
					handle_non_word_token(&tmp, new, &index[1]);
				tmp = tmp->next;
			}
		}
		append_to_exec(cmd, new);
		if (tmp && tmp->next)
			tmp = tmp->next;
	}
}
