/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:35:18 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/05 15:05:39 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_word_input(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

t_tokenizer	*make_node(char *input, int *j, t_lexer *type, t_stat *stat)
{
	t_tokenizer	*node;
	char		*s;

	if (*input == '\'')
		*stat = INQUOTES;
	else if (*input == '"')
		*stat = INDQUOTES;
	else
		*stat = GENERAL;
	s = ft_substr(input, *j, *j + 1);
	node = new_token(s, &type[0], stat, false);
	return (node);
}

t_tokenizer	*token_word(char *input, t_lexer *type, int *i)
{
	t_tokenizer	*node;
	int			j;
	t_stat		*stat;

	j = 0;
	stat = o_malloc(sizeof(t_stat));
	*stat = GENERAL;
	while (input[*i] && !check_word_input(input[*i]))
	{
		j++;
		if (input[*i] == '\'')
		{
			if (!check_squotes(&stat, input, i, &j))
				return (NULL);
		}
		else if (input[*i] == '"')
		{
			if (!check_dquotes(&stat, input, i, &j))
				return (NULL);
		}
		(*i)++;
	}
	node = new_token(ft_substr(input, *i - j, *i), type, stat, false);
	return (node);
}

t_tokenizer	*sub_redirection(char *input, t_lexer *type, \
	int *i, t_stat *stat)
{
	t_tokenizer	*node;
	int			j;
	static int	count;

	1 && (j = *i, node = NULL);
	if (input[*i] && input[*i] == '>' && input[*i + 1] == '>')
	{
		node = new_token(ft_substr(input, j, j + 2), &type[5], stat, false);
		(*i)++;
	}
	else if (input[*i] && input[*i] == '>' && input[*i + 1] != '>')
		node = make_node(input, &j, &type[4], stat);
	else if (input[*i] && input[*i] == '<' && input[*i + 1] == '<')
	{
		count++;
		node = new_token(ft_substr(input, j, j + 2), &type[7], stat, false);
		(*i)++;
	}
	else if (input[*i] && input[*i] == '<' && input[*i + 1] != '<')
		node = make_node(input, &j, &type[6], stat);
	else if (input[*i] && input[*i] == ' ')
		node = make_node(input, &j, &type[3], stat);
	if (count == 17)
		throw_error();
	return (node);
}

t_tokenizer	*token_special_char(char *input, t_lexer *type, int *i)
{
	t_tokenizer	*node;
	int			j;
	t_stat		*stat;

	node = NULL;
	j = *i;
	stat = o_malloc(sizeof(t_stat));
	if (input[*i] && input[*i] == '|')
		node = make_node(input, i, &type[1], stat);
	else if (input[*i] && input[*i] == '"')
		node = check_double_quotes(input, i, type, stat);
	else if (input[*i] && input[*i] == '\'')
		node = check_signle_quotes(input, i, type, stat);
	else
		node = sub_redirection(input, type, i, stat);
	if (input[*i])
		(*i)++;
	return (node);
}
