/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:23:24 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/31 16:13:05 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	process_dollar_dollar(char *token, int *i, t_minishell **mini)
{
	int	nbr;

	nbr = 0;
	while (token[*i] == '$' && token[*i + 1] == '$')
	{
		(*i)++;
		nbr++;
	}
	(*mini)->count = nbr;
}

static void	process_dollar_var(char *token, int *i, \
	char **join_it, t_minishell **mini)
{
	char	*str;
	int		j;

	if ((*mini)->count % 2 == 0)
	{
		(*i)++;
		j = *i;
		while (ft_isalnum(token[*i]) || token[*i] == '_'\
			|| ft_isalpha(token[*i]))
			(*i)++;
		str = get_value(mini, ft_substr(token, j, *i));
		*join_it = ft_strjoin(*join_it, str);
	}
}

static void	process_dollar(char *token, int *i, \
	char **join_it, t_minishell *mini)
{
	mini->count = 0;
	process_dollar_question(token, i, join_it, mini);
	process_dollar_dollar(token, i, &mini);
	process_dollar_var(token, i, join_it, &mini);
}

static void	process_non_dollar(char *token, int *i, char **join_it)
{
	char	*str;
	int		j;

	j = *i;
	while (token[*i] && token[*i] != '$')
		(*i)++;
	str = ft_substr(token, j, *i);
	*join_it = ft_strjoin(*join_it, str);
}

char	*expansion(char *token, t_minishell *mini)
{
	char	*join_it;
	int		i;

	i = 0;
	join_it = NULL;
	while (token[i])
	{
		if (token[i] == '$')
			process_dollar(token, &i, &join_it, mini);
		else
			process_non_dollar(token, &i, &join_it);
	}
	if (join_it)
		token = ft_strdup(join_it);
	return (token);
}
