/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:56:11 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 17:46:21 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	first_commande(t_minishell *mini, t_cmd *cmd)
{
	pid_t	pid;

	mini->pipe[0] = (int *)malloc(sizeof(int) * 2);
	if (pipe(mini->pipe[0]) == -1)
		return (perror("pipe"), ERROR);
	reset_sigs();
	pid = fork();
	if (pid == -1)
		return (perror("fork"), ERROR);
	if (!pid)
	{
		close(mini->pipe[0][0]);
		process(mini, cmd, STDIN_FILENO, mini->pipe[0][1]);
	}
	else
		if (close(mini->pipe[0][1]) == -1)
			return (perror("close"), ERROR);
	return (0);
}

int	other_cmds(t_minishell *mini, t_cmd *cmd, int i)
{
	pid_t	pid;

	mini->pipe[i] = (int *)malloc(sizeof(int) * 2);
	if (pipe(mini->pipe[i]) == -1)
		return (perror("pipe"), ERROR);
	reset_sigs();
	pid = fork();
	if (pid == -1)
		return (perror("fork"), ERROR);
	if (!pid)
	{
		close(mini->pipe[i][0]);
		process(mini, cmd, mini->pipe[i - 1][0], mini->pipe[i][1]);
	}
	else
	{
		if (close(mini->pipe[i][1]) == -1)
			return (perror("close"), ERROR);
		if (close(mini->pipe[i - 1][0]) == -1)
			return (perror("close"), ERROR);
	}
	return (0);
}

int	last_cmd(t_minishell *mini, t_cmd *cmd, int i)
{
	pid_t	pid;

	reset_sigs();
	pid = fork();
	if (pid == -1)
		return (perror("fork"), ERROR);
	if (!pid)
	{
		process(mini, cmd, mini->pipe[i - 2][0], STDOUT_FILENO);
	}
	if (close(mini->pipe[i - 2][0]))
		return (perror("close"), ERROR);
	waitpid(pid, &mini->ret_value, 0);
	return (0);
}

int	multi_process(t_minishell *mini, t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;

	tmp = cmds;
	first_commande(mini, tmp);
	tmp = tmp->next;
	i = 1;
	while (tmp->next && g_exit_stts != 6)
	{
		other_cmds(mini, tmp, i);
		tmp = tmp->next;
		i++;
	}
	i++;
	if (g_exit_stts != 6)
		last_cmd(mini, tmp, i);
	while (wait(NULL) > 0)
		;
	mini->ret_value = getexstatus(mini->ret_value);
	return (mini->ret_value);
}
