/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:20:32 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/05 16:40:42 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**find_path(t_minishell *env)
{
	t_env	*tmp;

	tmp = env->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PATH", 4))
			return (ft_split(tmp->value, ':'));
		tmp = tmp->next;
	}
	return (NULL);
}

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

char	*join_cmd_path(t_minishell *mini, char *cmd)
{
	char		**path;
	char		*full_path;
	int			i;

	if (!cmd || !cmd[0])
		return (NULL);
	if (is_directory(cmd))
		exit(IS_DIR);
	if (!access(cmd, F_OK) || !access(cmd, X_OK))
		return (cmd);
	path = find_path(mini);
	if (!path)
		return (NULL);
	full_path = ft_strjoin("/", cmd);
	i = -1;
	while (path[++i])
	{
		cmd = ft_strjoin(path[i], full_path);
		if (!access(cmd, F_OK) || !access(cmd, X_OK))
			return (cmd);
	}
	return (NULL);
}

char	*find_cmd(t_minishell *mini, char *cmd)
{
	char	*path;

	path = join_cmd_path(mini, cmd);
	if (path)
		return (path);
	return (NULL);
}

int	my_execve(t_minishell *mini, t_cmd *cmds)
{
	char	*path;
	char	**my_env;

	my_env = env_to_array(mini->env);
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
