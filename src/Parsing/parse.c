/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:55:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/31 17:05:07 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_validation(t_tokenizer *token, t_minishell *mini)
{
	if (token && *token->type == PIPE)
		return (printf("syntax error near unexpected token `%s'\n", \
			token->token), 0);
	while (token)
	{
		if (g_exit_stts == 6)
			return (-1);
		if (token && *token->type != WORD && !token->next)
			return (printf("syntax error near unexpected token `%s'\n", \
				token->token), 0);
		if (*token->type == LESSLESS && *token->next->type == WORD)
			if (!here_doc(token->next, mini))
				return (0);
		if (*token->type != WORD)
		{
			if (token->next)
				if (*token->next->type == PIPE)
					return (printf("syntax error near unexpected token `%s'\n", \
						token->token), 0);
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
	int			i;

	tmp = token;
	while (tmp)
	{
		i = 0;
		if (*tmp->stat == INDQUOTES)
			tmp->token = remove_dquotes(tmp, &i);
		else if (*tmp->stat == INQUOTES)
			tmp->token = remove_squotes(tmp, &i);
		tmp = tmp->next;
	}
}

void	join_tokens(t_tokenizer *token)
{
	t_tokenizer	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->joinable == 1)
		{
			tmp->token = ft_strjoin(tmp->token, tmp->next->token);
			tmp->next = tmp->next->next;
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
	join_tokens(mini->start);
	if (mini->start)
	{
		send_to_execution(mini->start, cmds);
		mini->cmd = *cmds;
		mini->ret_value = execution(mini, *cmds);
	}
}
