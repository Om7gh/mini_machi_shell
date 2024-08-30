/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:45:21 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/29 16:51:09 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*new_env(char *key, char *value)
{
	t_env	*head;

	head = o_malloc(sizeof(t_env));
	if (value)
		head->value = ft_strdup(value);
	else
		head->value = NULL;
	if (key)
		head->key = ft_strdup(key);
	else
		head->key = NULL;
	head->next = NULL;
	return (head);
}

void	append_env(t_env **env, t_env *node)
{
	t_env	*head;

	if (!env || !node)
		return ;
	if (!*env)
	{
		*env = node;
		return ;
	}
	head = *env;
	while (head->next)
		head = head->next;
	head->next = node;
}

void	del_one_env(t_env *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->value);
	del(lst->key);
	free(lst);
}

void	clear_env(t_env **lst, void (*del)(void *))
{
	t_env	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del_one_env(*lst, del);
		*lst = tmp;
	}
	lst = NULL;
}

int	store_env(char **envr, t_env **env)
{
	t_env	*node;
	int		i;
	char	**each_env;

	i = 0;
	if (!envr)
		return (0);
	while (envr && envr[i])
	{
		each_env = ft_split(envr[i], '=');
		if (!each_env)
			return (0);
		node = new_env(each_env[0], each_env[1]);
		if (!node)
			return (0);
		append_env(env, node);
		free(each_env);
		i++;
	}
	return (1);
}
