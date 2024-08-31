/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_pro_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:23:13 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/30 20:03:54 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (SUCCESS);
}

int	between_pipe(t_tokenizer *lst)
{
	int		length;

	if (!lst)
		return (0);
	length = 1;
	while (lst)
	{
		if (*lst->type == PIPE)
			length++;
		lst = lst->next;
	}
	return (length);
}

void	count_len(t_tokenizer *lst, int *commands_len, int *redirection_len)
{
	t_tokenizer	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp && *tmp->type != PIPE)
	{
		if (tmp && (*tmp->type == LESS || *tmp->type == GREAT \
			|| *tmp->type == LESSLESS || *tmp->type == GREATGREAT))
		{
			*redirection_len += 2;
			tmp = tmp->next->next;
			continue ;
		}
		else if (*tmp->type == WORD)
		{
			(*commands_len)++;
			tmp = tmp->next;
		}
	}
}

int	is_special(int c)
{
	return (c == '|' || c == '>' || c == '<' || c == ' ' || \
		c == '"' || c == '\'');
}

int	word_char(char c)
{
	return (c == '_' || c == '$');
}
