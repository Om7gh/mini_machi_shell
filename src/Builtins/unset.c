/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:01 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/30 16:03:59 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_unset(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| c == '_' || c == '>' || c == '<');
}

int	is_valid_identifier(char *cmd)
{
	if (!check_unset(cmd[0]))
	{
		printf("unset: `%s': not a valid identifier\n", cmd);
		return (0);
	}
	return (1);
}

int	unset_first(t_env **env, t_cmd *cmd, int i)
{
	t_env	*tmp;

	tmp = *env;
	if (!ft_strncmp(cmd->cmd[i], tmp->key, ft_strlen(tmp->key)))
	{
		*env = tmp->next;
		return (1);
	}
	return (0);
}

int	unset_env_var(t_env **env, t_cmd *cmd, int i)
{
	t_env	*tmp;
	t_env	*prev;
	int		flag;

	tmp = *env;
	prev = *env;
	flag = 0;
	while (tmp)
	{
		if (!ft_strcmp(cmd->cmd[i], tmp->key))
		{
			if (tmp == *env)
				*env = (*env)->next;
			else
				prev->next = tmp->next;
			flag = 1;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (flag);
}

int	unset(t_cmd *cmd, t_env **env)
{
	int	i;
	int	flag;

	if (!cmd->cmd[1])
		return (0);
	i = 1;
	while (cmd->cmd[i])
	{
		if (!env || !*env)
			return (0);
		if (!is_valid_identifier(cmd->cmd[i]))
			return (1);
		if (unset_first(env, cmd, i))
		{
			i++;
			continue ;
		}
		flag = unset_env_var(env, cmd, i);
		if (!flag)
			return (0);
		i++;
	}
	return (0);
}
