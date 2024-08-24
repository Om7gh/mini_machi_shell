/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:01 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 18:13:10 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_unset(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| c == '_' || c == '>' || c == '<');
}

int	unset(t_cmd *cmd, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;
	int		flag;
	int		i;

	if (!cmd->cmd[1])
		return (0);
	tmp = *env;
	prev = *env;
	i = 1;
	while (cmd->cmd[i])
	{
		tmp = *env;
		prev = *env;
		flag = 0;
		if (!check_unset(cmd->cmd[0][0]))
			return (printf("unset: `%s': not a valid identifier\n", cmd->cmd[i]), 1);
		else if (!ft_strcmp(cmd->cmd[i], tmp->key))
		{
			*env = tmp->next;
			if (cmd->cmd[i + 1])
				i++;
			continue ;
		}
		else
		{
			while (tmp)
			{
				if (!ft_strcmp(cmd->cmd[i], tmp->key))
				{
					if (tmp == *env)
						(*env) = (*env)->next;
					else
						prev->next = tmp->next;
					flag = 1;
					break ;
				}
				prev = tmp;
				tmp = tmp->next;
			}
		}
		if (!flag)
			return (0);
		i++;
	}
	return (0);
}
