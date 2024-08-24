/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:00:29 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/05 15:05:47 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_type(t_lexer lexer)
{
	if (lexer == WORD)
		printf("type : WORD\t");
	else if (lexer == WHITESPACE)
		printf("type : WHITESPACE\t");
	else if (lexer == D_QUOTE)
		printf("type : D_QUOTE\t");
	else if (lexer == QUOTE)
		printf("type : QUOTE\t");
	else if (lexer == PIPE)
		printf("type : PIPE\t");
	else if (lexer == LESS)
		printf("type : LESS\t");
	else if (lexer == LESSLESS)
		printf("type : LESSLESS\t");
	else if (lexer == GREAT)
		printf("type : GREATER\t");
	else if (lexer == GREATGREAT)
		printf("type : GREATER_GREATER\t");
	else
		printf("NO TYPE\t");
}

void	print_state(t_stat stat)
{
	if (stat == GENERAL)
		printf("stat GENERAL\t");
	else if (stat == INQUOTES)
		printf("stat INQUOTES\t");
	else if (stat == INDQUOTES)
		printf("stat INDQUOTES\t");
	else
		printf("NO STAT\t");
}

void	print_token(t_tokenizer	*token)
{
	while (token)
	{
		printf("token : [%s]\t\t", token->token);
		print_type(*(token->type));
		print_state(*(token->stat));
		printf("len %zu\n", token->len);
		token = token->next;
	}
}
