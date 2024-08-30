/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:41:48 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/29 14:50:45 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	here_hundle(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_stts = 6;
		close(0);
	}
}

void	here_doc_hundle(t_tokenizer *delimiter, t_minishell *mini)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, here_hundle);
		input = readline("> ");
		if (!input || (!ft_strncmp(input, delimiter->token,
					ft_strlen(delimiter->token))
				&& ft_strlen(input) == ft_strlen(delimiter->token)))
		{
			free(input);
			break ;
		}
		if (*delimiter->stat == GENERAL)
			input = expansion(input, mini);
		write(mini->fdin, input, ft_strlen(input));
		write(mini->fdin, "\n", 1);
		free(input);
	}
}

int	here_doc(t_tokenizer *delimiter, t_minishell *mini)
{
	mini->fdin = open("/tmp/ana_machi_heredoc", \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (mini->fdin == -1)
		return (perror("open"), 0);
	mini->here_cpy = dup(0);
	here_doc_hundle(delimiter, mini);
	if (g_exit_stts == 6)
		mini->ret_value = 1;
	dup2(mini->here_cpy, 0);
	mini->infile = open("/tmp/ana_machi_heredoc", O_RDONLY, 0777);
	if (mini->infile == -1)
		return (perror("open"), 0);
	close(mini->fdin);
	return (1);
}
