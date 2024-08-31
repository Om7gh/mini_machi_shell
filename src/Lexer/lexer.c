/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 05:59:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/31 19:08:25 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	throw_error(void)
{
	ft_putendl_fd("minishell: maximum here_document count exceeded", 2);
	exit(2);
}

int	fill_token_list(char *input, \
	t_tokenizer **token, t_lexer *type, t_tokenizer *node)
{
	int			i;

	i = 0;
	while (input[i])
	{
		if (g_exit_stts == 6)
			return (0);
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

int	lexer_first(t_tokenizer **token, char *input)
{
	t_tokenizer	*node;
	t_lexer		*type;

	node = NULL;
	type = o_malloc(sizeof(t_lexer) * 10);
	type[0] = WORD;
	type[1] = PIPE;
	type[3] = WHITESPACE;
	type[4] = GREAT;
	type[5] = GREATGREAT;
	type[6] = LESS;
	type[7] = LESSLESS;
	type[8] = QUOTE;
	type[9] = D_QUOTE;
	if (!fill_token_list(input, token, type, node))
		return (0);
	return (1);
}
