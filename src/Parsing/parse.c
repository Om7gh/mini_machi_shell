/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:55:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/30 15:35:35 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	word_char(char c)
{
	return (c == '_' || c == '$');
}

int	check_validation(t_tokenizer *token, t_minishell *mini)
{
	if (token && *token->type == PIPE)
		return (printf("syntax error near unexpected \
			token `%s'\n", token->token), 0);
	while (token)
	{
		if (g_exit_stts == 6)
			return (-1);
		if (token && *token->type != WORD && !token->next)
			return (printf("syntax error near \
				unexpected token `%s'\n", token->token), 0);
		if (*token->type == LESSLESS && *token->next->type == WORD)
			if (!here_doc(token->next, mini))
				return (0);
		if (*token->type != WORD)
		{
			if (token->next)
				if (*token->next->type == PIPE)
					return (printf("syntax error near unexpected \
						token `%s'\n", token->token), 0);
		}
		if (ft_strchr(token->token, '$') && *token->stat != INQUOTES)
			token->token = expansion(token->token, mini);
		token = token->next;
	}
	return (1);
}

void	remove_quotes(t_tokenizer *token)
{
	t_tokenizer	*tmp;
	char		*str;
	int			i;

	tmp = token;
	while (tmp)
	{
		str = NULL;
		i = 0;
		if (*tmp->stat == INDQUOTES)
		{
			while (tmp->token[i])
			{
				if (tmp->token[i] != '"')
					str = ft_strjoin(str, ft_substr(tmp->token, i, i + 1));
				if (tmp->token[i])
					i++;
			}
			if (str)
				tmp->token = ft_strdup(str);
		}
		else if (*tmp->stat == INQUOTES)
		{
			while (tmp->token[i])
			{
				if (tmp->token[i] != '\'')
					str = ft_strjoin(str, ft_substr(tmp->token, i, i + 1));
				if (tmp->token[i])
					i++;
			}
			if (str)
				tmp->token = ft_strdup(str);
		}
		tmp = tmp->next;
	}
}

void	parse_input(t_minishell *mini, t_cmd **cmds)
{
	int	checker;

	checker = check_validation(mini->start, mini);
	if (checker == 0)
		return ;
	else if (checker == -1)
	{
		mini->ret_value = 1;
		return ;
	}
	remove_quotes(mini->start);
	if (mini->start)
	{
		send_to_execution(mini->start, cmds);
		mini->cmd = *cmds;
		mini->ret_value = execution(mini, *cmds);
	}
}
