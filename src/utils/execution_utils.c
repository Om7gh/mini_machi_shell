/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:54:01 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 17:23:34 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	node_len(t_cmd *cmds)
{
	int		length;
	t_cmd	*tmp;

	if (!cmds)
		return (0);
	length = 0;
	tmp = cmds;
	while (tmp)
	{
		length++;
		tmp = tmp->next;
	}
	return (length);
}

char	*fill_envs(char const *s1, char const *s2, char **res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1)
	{
		i = -1;
		while (*(s1 + ++i))
			*(*res + i) = *(s1 + i);
	}
	if (s2)
	{
		*(*res + i++) = '=';
		j = 0;
		while (*(s2 + j))
			*(*res + i++) = *(s2 + j++);
	}
	*(*res + i) = '\0';
	return (*res);
}

char	*env_join(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	char	*res;

	l1 = 0;
	l2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		l1 = ft_strlen(s1);
	if (s2)
		l2 = 1 + ft_strlen(s2);
	res = malloc((l1 + l2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	return (fill_envs(s1, s2, &res));
}

static int	envname_size(t_env *env)
{
	int	i;

	if (!env)
		return (0);
	i = 1;
	while (env->next)
	{
		if (env->key && env->value)
			i++;
		env = env->next;
	}
	return (i);
}

char	**env_to_array(t_env *env_list)
{
	int		i;
	int		size;
	char	**env;

	if (!env_list)
		return (NULL);
	size = envname_size(env_list);
	env = malloc(sizeof(char *) * (size + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (env_list)
	{
		if (env_list->key && env_list->value)
		{
			*(env + i) = env_join(env_list->key, env_list->value);
			i++;
		}
		env_list = env_list->next;
	}
	return (*(env + i) = NULL, env);
}
