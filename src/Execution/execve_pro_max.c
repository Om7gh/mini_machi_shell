/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_pro_max.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:35:34 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/13 12:43:28 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_directory(char *cmd)
{
	struct stat	file;

	if (stat(cmd, &file) == 0 && S_ISDIR(file.st_mode))
	{
		(write(2, "minishell: ", 11), write(2, cmd, ft_strlen(cmd)));
		write(2, " is a directory\n", 16);
		return (ERROR);
	}
	return (SUCCESS);
}

int	check_wrong_command(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK))
		{
			(write(2, "minishell: ", 11), write(2, cmd, ft_strlen(cmd)));
			write(2, ": No such file or directory\n", 28);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	my_execve(t_minishell *mini, t_cmd *cmds)
{
	char	*path;
	char	**my_env;

	my_env = env_to_array(mini->env);
	reset_sigs();
	if (cmds->cmd)
	{
		path = find_cmd(mini, cmds->cmd[0]);
		if (!path || !ft_strchr(path, '/'))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(ft_split(cmds->cmd[0], ' ')[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(UNKNOWN_COMMAND);
		}
		execve(path, cmds->cmd, my_env);
		perror("execve");
		exit(1);
	}
	return (0);
}
