/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:35:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 17:36:19 by kael-ala         ###   ########.fr       */
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
	int			count_red;
	int			count_cmd;

	tmp = token;
	while (tmp)
	{
		i = 0;
		j = 0;
		count_cmd = 0;
		count_red = 0;
		count_len(tmp, &count_cmd, &count_red);
		new = new_cmd(count_cmd, count_red);
		while (tmp && *tmp->type != PIPE)
		{
			if (*tmp->type == WORD)
			{
				new->cmd[i] = ft_strdup(tmp->token);
				i++;
			}
			else if (*tmp->type != WORD)
			{
				new->red[j] = ft_strdup(tmp->token);
				j++;
				new->red[j] = ft_strdup(tmp->next->token);
				j++;
				tmp = tmp->next;
			}
			tmp = tmp->next;
		}
		if (!new)
		{
			printf("error with malloc\n");
			return ;
		}
		append_to_exec(cmd, new);
		if (tmp && tmp->next)
			tmp = tmp->next;
	}
}
