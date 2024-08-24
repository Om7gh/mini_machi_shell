/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:28:58 by kael-ala          #+#    #+#             */
/*   Updated: 2024/08/21 17:22:36 by kael-ala         ###   ########.fr       */
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
			return (130);
		else if (ret == SIGQUIT)
			return (131);
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

void	handle_sigint_child(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_stts = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (sig == SIGQUIT)
	{
		g_exit_stts = 1;
		write(1, "QUIT: 3\n", 8);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	reset_sigs(void)
{
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, handle_sigint_child);
	signal(SIGTSTP, SIG_DFL);
}

void	set_sigs(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
