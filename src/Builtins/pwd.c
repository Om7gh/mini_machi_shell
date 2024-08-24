/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:51 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 18:10:30 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pwd(t_cmd *cmd)
{
	char	*path;

	path = cmd->cmd[0];
	path = getcwd(NULL, 0);
	if (!path)
	{
		printf("%spwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n%s", RED_COLOR, RESET);
		return (1);
	}
	printf("%s\n", path);
	return (0);
}
