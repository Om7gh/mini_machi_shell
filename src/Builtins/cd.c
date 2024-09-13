/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:38 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/13 12:18:58 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_values(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	set_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (value)
				tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	handle_chdir_error(char *path)
{
	if (!access(path, F_OK))
	{
		ft_putstr_fd("Minishell : cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(" Permission denied ", 2);
	}
	else
	{
		ft_putstr_fd("Minishell : cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(" No such file or directory ", 2);
	}
}

static void	update_pwd_env(char *oldpwd, char *pwd, t_env **env)
{
	if (!set_env(env, "OLDPWD", oldpwd))
		append_env(env, new_env("OLDPWD", ft_strdup("")));
	if (!set_env(env, "PWD", pwd))
		append_env(env, new_env("PWD", pwd));
	free(oldpwd);
	free(pwd);
}

int	cd(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (cmd->cmd[1] == NULL || (cmd->cmd[1] && !ft_strcmp(cmd->cmd[1], "~")))
	{
		path = get_values(&env, "HOME");
		if (chdir(path) == -1)
			return (free(oldpwd), handle_chdir_error(path), 1);
	}
	else
	{
		path = cmd->cmd[1];
		if (chdir(path) == -1)
		{
			handle_chdir_error(path);
			free(oldpwd);
			return (1);
		}
	}
	pwd = getcwd(NULL, 0);
	update_pwd_env(oldpwd, pwd, &env);
	return (0);
}
