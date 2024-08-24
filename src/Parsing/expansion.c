/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:23:24 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 17:31:34 by kael-ala         ###   ########.fr       */
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

char	*expansion(char *token, t_minishell *mini)
{
	char	*join_it;
	char	*str;
	int		i;
	int		j;
	int		count;

	i = 0;
	str = NULL;
	join_it = NULL;
	j = 0;
	while (token[i])
	{
		count = 0;
		if (token[i] == '$')
		{
			if (token[i] == '$' && token[i + 1] == '?')
			{
				str = ft_itoa(mini->ret_value);
				join_it = ft_strjoin(join_it, str);
				i++;
			}
			while (token[i] == '$' && token[i + 1] == '$')
				(count++, i++);
			if (count % 2 == 0)
			{
				i++;
				j = i;
				while (ft_isalnum(token[i]) || token[i] == '_'
					|| ft_isalpha(token[i]))
					i++;
				str = get_value(&mini, ft_substr(token, j, i));
				join_it = ft_strjoin(join_it, str);
			}
			else
			{
				j = i;
				while (token[i] && token[i] != ' ')
					i++;
				str = ft_substr(token, j - count, i);
				join_it = ft_strjoin(join_it, str);
			}
		}
		else if (token[i] != '$')
		{
			j = i;
			while (token[i] && token[i] != '$')
				i++;
			str = ft_substr(token, j, i);
			join_it = ft_strjoin(join_it, str);
		}
	}
	if (join_it)
		token = ft_strdup(join_it);
	return (token);
}
