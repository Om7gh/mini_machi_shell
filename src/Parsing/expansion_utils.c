/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:44:10 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/31 16:12:47 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_value(t_minishell **mini, char *key)
{
	t_env	*envr;

	if (!key)
		return (ft_strdup(""));
	envr = (*mini)->env;
	while (envr)
	{
		if (!strcmp(envr->key, key))
			return (envr->value);
		envr = envr->next;
	}
	return (ft_strdup(""));
}

void	process_dollar_question(char *token, int *i, \
	char **join_it, t_minishell *mini)
{
	char	*str;

	if (token[*i] == '$' && token[*i + 1] == '?')
	{
		str = ft_itoa(mini->ret_value);
		*join_it = ft_strjoin(*join_it, str);
		(*i)++;
	}
}
