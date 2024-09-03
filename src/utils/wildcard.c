/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:15:56 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/02 19:15:01 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*join_again(char **tmp)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	while (*tmp)
	{
		temp = str;
		str = ft_strjoin(str, *tmp);
		temp = str;
		str = ft_strjoin(str, " ");
		tmp++;
	}
	return (str);
}

char	*sort_wildcard(char *wildcard)
{
	char	**tmp;
	char	*tmp2;
	int		i;
	int		j;

	tmp = ft_split(wildcard, ' ');
	i = 0;
	while (tmp[i])
	{
		j = i + 1;
		while (tmp[j])
		{
			if (ft_strncmp(tmp[i], tmp[j], ft_strlen(tmp[j])) > 0)
			{
				tmp2 = tmp[i];
				tmp[i] = tmp[j];
				tmp[j] = tmp2;
			}
			j++;
		}
		i++;
	}
	return (join_again(tmp));
}

char	*ft_wildcard(char *dirname)
{
	DIR				*dir;
	struct dirent	*entry;
	int				status;
	char			*path;

	status = 0;
	dir = opendir(dirname);
	if (!dir)
		return (perror("opendir"), "");
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		path = ft_strjoin(path, entry->d_name);
		path = ft_strjoin(path, " ");
		entry = readdir(dir);
	}
	closedir(dir);
	path = sort_wildcard(path);
	return (path);
}
