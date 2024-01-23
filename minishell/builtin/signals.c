/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:22:21 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/06 13:25:15 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	antislash(int sig)
{
	int		i;
	t_data	*data;

	data = starton();
	i = -1;
	if (sig == SIGQUIT)
		exit(131);
	if (sig == SIGINT)
	{
		free_tab1(data->exec->path);
		free(data->exec->pids);
		free(data->exec);
		if (data->tb_cmd[0])
			free_tab2(data->tb_cmd);
		if (data->first != NULL)
			free_list(data->first);
		free_list_env(data->env_list);
		free_tab1(data->envi);
		while (++i < data->nb_here)
			free(data->here[i].delim);
		if (data->nb_here > 0)
			free(data->here);
		exit(130);
	}
}

void	reactiv(int sig)
{
	if (sig == SIGQUIT)
		exit(131);
}

void	ctrlc(int sig)
{
	t_data	*data;

	data = starton();
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		data->exit_code = 130;
	}
}

void	ctrlc_2(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

void	ctrlc_child(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(0);
	}
}
