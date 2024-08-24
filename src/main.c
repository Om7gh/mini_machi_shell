/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:21:47 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/21 17:19:20 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_all(void)
{
	int	i;

	i = 3;
	while (++i < OPEN_MAX)
		if (close(i) == -1)
			return ;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	t_tokenizer	*lexer;
	t_env		*envr;
	t_cmd		*cmds;

	(void)argc;
	(void)argv;
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!minishell)
	{
		printf("%serror with malloc%s\n", RED_COLOR, RESET);
		exit(ERROR);
	}
	envr = NULL;
	lexer = NULL;
	cmds = NULL;
	store_env(env, &envr);
	minishell->ret_value = 0;
	minishell->env = envr;
	rl_catch_signals = 0;
	while (1)
	{
		set_sigs();
		g_exit_stts = 0;
		minishell->line = readline("\x1b[32mminishell$ : \x1b[0m");
		if (!minishell->line)
			return (minishell->ret_value);
		if (g_exit_stts == 1)
			minishell->ret_value = 1;
		if (!lexer_first(&lexer, minishell->line))
			continue ;
		minishell->start = lexer;
		parse_input(minishell, &cmds);
		if (minishell->line)
		{
			add_history(minishell->line);
			close_all();
			free(minishell->line);
			clear_token(&lexer, free);
			clear_cmd(&cmds, free);
		}
	}
	return (minishell->ret_value);
}
