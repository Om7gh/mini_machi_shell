/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:20:32 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 17:45:44 by kael-ala         ###   ########.fr       */
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

char	*join_cmd_path(t_minishell *mini, char *cmd)
{
	char		**path;
	char		*full_path;
	struct stat	file;

	path = find_path(mini);
	if (!path)
		return (NULL);
	if (!cmd || !cmd[0])
		return (NULL);
	if (stat(cmd, &file) == 0 && S_ISDIR(file.st_mode))
	{
		(write(2, "minishell: ", 11), write(2, cmd, ft_strlen(cmd)));
		(write(2, " is a directory\n", 16), exit(IS_DIR));
	}
	if (!access(cmd, F_OK) || !access(cmd, X_OK))
		return (cmd);
	else
	{
		full_path = ft_strjoin("/", cmd);
		while (*path)
		{
			cmd = ft_strjoin(*path, full_path);
			if (!access(cmd, F_OK) || !access(cmd, X_OK))
				return (cmd);
			path++;
		}
		return (NULL);
	}
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
		if (path)
		{
			execve(path, cmds->cmd, my_env);
			perror("execve");
			exit(1);
		}
		else
		{
			ft_putstr_fd("minishell: commande ", 2);
			ft_putstr_fd(cmds->cmd[0], 2);
			ft_putendl_fd(" Not found", 2);
			exit(UNKNOWN_COMMAND);
		}
	}
	return (0);
}
