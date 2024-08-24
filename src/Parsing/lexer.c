/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 05:59:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/07 20:48:41 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_word_input(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ')
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
	node = new_token(s, &type[0], stat);
	return (node);
}

t_tokenizer	*token_word(char *input, t_lexer *type, int *i)
{
	t_tokenizer	*node;
	int			j;
	char		*s;
	t_stat		*stat;

	j = 0;
	stat = malloc(sizeof(t_stat));
	*stat = GENERAL;
	while (input[*i] && !check_word_input(input[*i]))
	{
		j++;
		if (input[*i] == '\'')
		{
			*stat = INQUOTES;
			(*i)++;
			while (input[*i] && input[*i] != '\'')
			{
				j++;
				(*i)++;
			}
			if (input[*i] != '\'')
				return (printf("error with single quotes\n"), NULL);
			j++;
		}
		else if (input[*i] == '"')
		{
			*stat = INDQUOTES;
			(*i)++;
			while (input[*i] && input[*i] != '"')
			{
				j++;
				(*i)++;
			}
			if (input[*i] != '"')
				return (printf("error with single quotes\n"), NULL);
			j++;
		}
		(*i)++;
	}
	s = ft_substr(input, *i - j, *i);
	node = new_token(s, type, stat);
	return (node);
}

t_tokenizer	*token_special_char(char *input, t_lexer *type, int *i)
{
	t_tokenizer	*node;
	char		*s;
	int			j;
	t_stat		*stat;

	node = NULL;
	s = NULL;
	j = *i;
	stat = malloc(sizeof(t_stat));
	if (input[*i] && input[*i] == '|')
		node = make_node(input, i, &type[1], stat);
	else if (input[*i] && input[*i] == '"')
		node = check_double_quotes(input, i, type, stat);
	else if (input[*i] && input[*i] == '\'')
		node = check_signle_quotes(input, i, type, stat);
	else if (input[*i] && input[*i] == '>' && input[*i + 1] == '>')
	{
		s = ft_substr(input, j, j + 2);
		node = new_token(s, &type[5], stat);
		(*i)++;
	}
	else if (input[*i] && input[*i] == '>' && input[*i + 1] != '>')
		node = make_node(input, &j, &type[4], stat);
	else if (input[*i] && input[*i] == '<' && input[*i + 1] == '<')
	{
		s = ft_substr(input, j, j + 2);
		node = new_token(s, &type[7], stat);
		(*i)++;
	}
	else if (input[*i] && input[*i] == '<' && input[*i + 1] != '<')
		node = make_node(input, &j, &type[6], stat);
	else if (input[*i] && input[*i] == ' ')
		node = make_node(input, &j, &type[3], stat);
	if (input[*i])
		(*i)++;
	return (node);
}

int	lexer_first(t_tokenizer **token, char *input)
{
	t_tokenizer	*node;
	int			i;
	t_lexer		*type;

	type = malloc(sizeof(t_lexer) * 10);
	type[0] = WORD;
	type[1] = PIPE;
	type[3] = WHITESPACE;
	type[4] = GREAT;
	type[5] = GREATGREAT;
	type[6] = LESS;
	type[7] = LESSLESS;
	type[8] = QUOTE;
	type[9] = D_QUOTE;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		if (input[i] && !is_special(input[i]) && !ft_isspace(input[i]))
			node = token_word(input, type, &i);
		else if (input[i] && is_special(input[i]))
			node = token_special_char(input, type, &i);
		if (!node)
			return (clear_token(token, free), 0);
		append_token(token, node);
	}
	return (1);
}
