/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:28:58 by kael-ala          #+#    #+#             */
/*   Updated: 2024/09/13 12:41:34 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	getexstatus(int stts)
{
	int	ret;

	if (WIFSIGNALED(stts))
	{
		ret = WTERMSIG(stts);
		if (ret == SIGINT)
			return (write(1, "\n", 1), 130);
		else if (ret == SIGQUIT)
			return (write(1, "QUIT: 3\n", 8), 131);
		else
			return (128 + ret);
	}
	return (WEXITSTATUS(stts));
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_stts = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	reset_sigs(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}

void	set_sigs(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
