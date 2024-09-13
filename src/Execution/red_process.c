/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:49:32 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/13 11:23:42 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	send_redir(char *red, int output)
{
	int	fd;

	fd = open(red, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	if (dup2(fd, output) < 0)
	{
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

int	append_redir(char *red, int output)
{
	int	fd;

	fd = open(red, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	if (dup2(fd, output) < 0)
	{
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

int	read_redir(char *red, int input)
{
	int	fd;

	fd = open(red, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	if (dup2(fd, input) < 0)
	{
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

int	heredoc(t_minishell *mini, int input)
{
	(void)input;
	if (dup2(mini->infile, STDIN_FILENO) < 0)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}

int	red_process(t_minishell *mini, t_cmd *cmds, int input, int output)
{
	int		i;
	int		j;
	t_cmd	*tmp;

	i = 0;
	j = 0;
	tmp = cmds;
	while (tmp && tmp->red && tmp->red[j])
	{
		if (!ft_strcmp(tmp->red[j], ">"))
			i = send_redir(tmp->red[j + 1], output);
		else if (!ft_strcmp(tmp->red[j], ">>"))
			i = append_redir(tmp->red[j + 1], output);
		else if (!ft_strcmp(tmp->red[j], "<"))
			i = read_redir(tmp->red[j + 1], input);
		else if (!ft_strcmp(tmp->red[j], "<<"))
			i = heredoc(mini, input);
		j++;
		if (i < 0)
			return (-1);
	}
	return (0);
}
