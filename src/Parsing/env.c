/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:45:21 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 17:29:12 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*new_env(char *key, char *value)
{
	t_env	*head;

	head = (t_env *)malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->value = value;
	head->key = key;
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
	while (envr[i])
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
