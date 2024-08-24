/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:20:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 17:35:31 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tokenizer	*check_signle_quotes(char *input, int *i, t_lexer *type, \
		t_stat *stat)
{
	t_tokenizer	*node;
	int			k;
	char		*s;

	if (input[*i] == '\'')
	{
		(*i)++;
		k = *i;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		if (input[*i] == '\'')
		{
			(*i)++;
			if (input[*i] == '\'')
				return (printf("error with single quotes\n"), NULL);
			while (input[*i] && !check_word_input(input[*i]))
				(*i)++;
			*stat = INQUOTES;
			s = ft_substr(input, k, *i);
			node = new_token(s, type, stat);
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

	if (input[*i] == '"')
	{
		(*i)++;
		k = *i;
		while (input[*i] && input[*i] != '"')
			(*i)++;
		if (input[*i] == '"')
		{
			(*i)++;
			if (input[*i] == '"')
				return (printf("error with single quotes\n"), NULL);
			while (input[*i] && !check_word_input(input[*i]))
				(*i)++;
			*stat = INDQUOTES;
			s = ft_substr(input, k, *i);
			node = new_token(s, type, stat);
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
