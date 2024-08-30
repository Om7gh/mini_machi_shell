/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:12:48 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/30 17:53:08 by omghazi          ###   ########.fr       */
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

void	check_id(char *id, char *arg, int *join_flag, int *error)
{
	int		i;

	i = 1;
	while (id[i])
	{
		if (i == (int)ft_strlen(id) - 1)
		{
			if (join_string(id[i], arg[i + 1], \
				i == (int)ft_strlen(id) - 1, join_flag))
			{
				i++;
				continue ;
			}
		}
		if (!ft_isalnum(id[i]) && id[i] != '_')
			*error = 1;
		i++;
	}
}

int	isvalid(char *arg, int *join_flag)
{
	int		error;
	char	*id;

	error = 0;
	if (!arg)
		return (0);
	if (ft_strchr(arg, '='))
		id = ft_substr(arg, 0, ft_strnchr(arg, '='));
	else
		id = arg;
	if (!ft_isalpha(id[0]) && id[0] != '_')
		return (0);
	check_id(id, arg, join_flag, &error);
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
