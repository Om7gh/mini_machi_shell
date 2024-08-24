/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:37:09 by kael-ala          #+#    #+#             */
/*   Updated: 2024/08/21 18:09:36 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strnchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (0);
}

int	join_string(char c, char next_c, int is_last, int *flag)
{
	if (c == '+' && is_last
		&& next_c && next_c == '=')
	{
		*flag = 1;
		return (1);
	}
	return (0);
}

int	isvalid(char *arg, int *join_flag)
{
	int		i;
	int		error;
	char	*id;

	i = 1;
	error = 0;
	if (!arg)
		return (0);
	if (ft_strchr(arg, '='))
		id = ft_substr(arg, 0, ft_strnchr(arg, '='));
	else
		id = arg;
	if (!ft_isalpha(id[0]) && id[0] != '_')
		return (0);
	while (id[i])
	{
		if (i == (int)ft_strlen(id) - 1)
		{
			if (join_string(id[i], arg[i + 1], i == (int)ft_strlen(id) - 1, join_flag))
			{
				i++;
				continue ;
			}
		}
		if (!ft_isalnum(id[i]) && id[i] != '_')
			error = 1;
		i++;
	}
	if (error)
		return (0);
	return (1);
}

void	split_var(char *arg, char **id, char **value, int flag)
{
	*id = NULL;
	*value = NULL;
	if (!ft_strchr(arg, '='))
		*id = arg;
	else if (flag)
	{
		*id = ft_substr(arg, 0, ft_strnchr(arg, '=') - 1);
		*value = ft_substr(arg, ft_strnchr(arg, '=') + 1, ft_strlen(arg));
	}
	else
	{
		*id = ft_substr(arg, 0, ft_strnchr(arg, '='));
		*value = ft_substr(arg, ft_strnchr(arg, '=') + 1, ft_strlen(arg));
	}
}

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else if (tmp->key && !tmp->value)
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

void	add_new_node(char *id, char *value, t_env **env)
{
	t_env	*new;

	new = new_env(id, value);
	append_env(env, new);
}

void	add_value(char *id, char *value, t_env **env, int flag)
{
	t_env	*tmp;
	int		found;

	tmp = *env;
	found = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, id) == 0 && !flag)
		{
			tmp->value = value;
			found = 1;
		}
		else if (ft_strcmp(tmp->key, id) == 0 && flag)
		{
			tmp->value = ft_strjoin(tmp->value, value);
			found = 1;
		}
		tmp = tmp->next;
	}
	if (!found)
		add_new_node(id, value, env);
}

int	export(t_cmd *cmd, t_env **env)
{
	int		i;
	int		flag;
	char	*id;
	char	*value;

	i = 1;
	flag = 0;
	if (!cmd->cmd[1] || (ft_strlen(cmd->cmd[1]) == 0 && !cmd->cmd[2]))
		print_export(*env);
	else
	{
		while (cmd->cmd[i])
		{
			if (ft_strlen(cmd->cmd[i]) == 0)
				;
			else if (isvalid(cmd->cmd[i], &flag))
			{
				split_var(cmd->cmd[i], &id, &value, flag);
				add_value(id, value, env, flag);
			}
			else
				printf("export: %s: not a valid identifier\n", cmd->cmd[i]);
			i++;
		}
	}
	return (0);
}
