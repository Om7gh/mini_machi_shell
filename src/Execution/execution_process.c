/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:04:21 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 17:40:43 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	single_process(t_minishell *mini, t_cmd *cmds)
{
	int	status;

	mini->fdin = dup(STDIN_FILENO);
	mini->fdout = dup(STDOUT_FILENO);
	if (red_process(mini, cmds, STDIN_FILENO, STDOUT_FILENO) == -1)
		return (1);
	status = execute_single_commande(mini, cmds);
	dup2(mini->fdin, STDIN_FILENO);
	dup2(mini->fdout, STDOUT_FILENO);
	close(mini->fdin);
	close(mini->fdout);
	return (status);
}

int	execute_single_commande(t_minishell *mini, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (is_builtins(cmd))
		status = execute_builtin(mini, cmd);
	else
	{
		reset_sigs();
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			status = my_execve(mini, cmd);
		waitpid(pid, &status, 0);
		status = getexstatus(status);
	}
	return (status);
}

int	execute_builtin(t_minishell *mini, t_cmd *cmd)
{
	if (cmd && cmd->cmd && cmd->cmd[0])
	{
		if (!ft_strncmp(cmd->cmd[0], "export", 6)
			&& ft_strlen(cmd->cmd[0]) == 6)
			return (export(cmd, &mini->env));
		if (!ft_strncmp(cmd->cmd[0], "unset", 5) && ft_strlen(cmd->cmd[0]) == 5)
			return (unset(cmd, &mini->env));
		if (!ft_strncmp(cmd->cmd[0], "env", 3) && ft_strlen(cmd->cmd[0]) == 3)
			return (env(mini->env));
		if (!ft_strncmp(cmd->cmd[0], "exit", 4) && ft_strlen(cmd->cmd[0]) == 4)
			return (ft_exit(cmd, mini));
		if (!ft_strncmp(cmd->cmd[0], "cd", 2) && ft_strlen(cmd->cmd[0]) == 2)
			return (cd(cmd, mini->env));
		if (!ft_strncmp(cmd->cmd[0], "pwd", 3) && ft_strlen(cmd->cmd[0]) == 3)
			return (pwd(cmd));
		if (!ft_strncmp(cmd->cmd[0], "echo", 4) && ft_strlen(cmd->cmd[0]) == 4)
			return (echo(cmd));
	}
	return (0);
}
