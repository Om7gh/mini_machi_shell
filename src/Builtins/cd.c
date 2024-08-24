/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:38 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 17:55:07 by kael-ala         ###   ########.fr       */
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
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	cd(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	path = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!cmd->cmd[1])
	{
		path = get_values(&env, "HOME");
		if (chdir(path) == -1)
		{
			ft_putstr_fd("Minishell : cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(" No such file or directory ", 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
	}
	else
	{
		path = cmd->cmd[1];
		if (chdir(path) == -1)
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
			return (1);
		}
	}
	pwd = getcwd(NULL, 0);
	if (!set_env(&env, "OLDPWD", oldpwd))
		append_env(&env, new_env("OLDPWD", ft_strdup("")));
	if (!set_env(&env, "PWD", pwd))
		append_env(&env, new_env("PWD", pwd));
	return (0);
}
