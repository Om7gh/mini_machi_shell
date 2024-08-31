/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:20:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/31 16:31:31 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tokenizer	*check_signle_quotes(char *input, int *i, t_lexer *type, \
		t_stat *stat)
{
	t_tokenizer	*node;
	int			k;
	char		*s;
	bool		flag;

	flag = false;
	if (input[*i] == '\'')
	{
		(*i)++;
		k = *i;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		if (input[*i] == '\'')
		{
			*stat = INQUOTES;
			s = ft_substr(input, k, *i);
			if (!is_special(input[*i + 1]) && input[*i + 1] != '\0')
				flag = true;
			node = new_token(s, type, stat, flag);
			return (node);
		}
		return (printf("error with single quotes\n"), NULL);
	}
	return (printf("error with single quotes\n"), NULL);
}

t_tokenizer	*check_double_quotes(char *input, int *i, t_lexer *type, \
		t_stat *stat)
{
	t_tokenizer	*node;
	int			k;
	char		*s;
	bool		flag;

	flag = false;
	if (input[*i] == '"')
	{
		(*i)++;
		k = *i;
		while (input[*i] && input[*i] != '"')
			(*i)++;
		if (input[*i] == '"')
		{
			*stat = INDQUOTES;
			s = ft_substr(input, k, *i);
			if (!is_special(input[*i + 1]) && input[*i + 1] != '\0')
				flag = true;
			node = new_token(s, type, stat, flag);
			return (node);
		}
		return (printf("error with single quotes\n"), NULL);
	}
	return (printf("error with single quotes\n"), NULL);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

int	check_squotes(t_stat **stat, char *input, int *i, int *j)
{
	**stat = INQUOTES;
	(*i)++;
	while (input[*i] && input[*i] != '\'')
	{
		(*j)++;
		(*i)++;
	}
	if (input[*i] != '\'')
		return (printf("error with single quotes\n"), 0);
	(*j)++;
	return (1);
}

int	check_dquotes(t_stat **stat, char *input, int *i, int *j)
{
	**stat = INDQUOTES;
	(*i)++;
	while (input[*i] && input[*i] != '"')
	{
		(*j)++;
		(*i)++;
	}
	if (input[*i] != '"')
		return (printf("error with double quotes\n"), 0);
	(*j)++;
	return (1);
}
