/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:02:01 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 15:25:18 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exit_hd(int sig)
{
	t_data	*data;
	int		i;

	signal(SIGINT, &exit_hd);
	data = starton();
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		i = -1;
		while (++i < data->nb_here)
		{
			close_fd(&data->here[i].pipe[1]);
			close_fd(&data->here[i].pipe[0]);
		}
		free_data_2(data);
		exit(130);
	}
}

void	child_hd(t_data *data, char *str)
{
	int	i;

	signal(SIGINT, &exit_hd);
	data->n = data->n + 1;
	free(str);
	i = -1;
	while (++i < data->nb_here)
		openfileshd(i, data->here);
	free_tab1(data->exec->path);
	free(data->exec->pids);
	free(data->exec);
	i = 0;
	while (i < data->nb_here)
	{
		free(data->here[i].delim);
		i++;
	}
	free (data->here);
	if (data->tb_cmd[0])
		free_tab2(data->tb_cmd);
	if (data->first != NULL)
		free_list(data->first);
	free_list_env(data->env_list);
	free_tab1(data->envi);
	exit(1);
}

char	*openfileshd(int index, t_here *here)
{
	char	*s;

	while (1)
	{
		s = readline("here_doc> ");
		if (!s || !ft_strcmp(s, here[index].delim))
			break ;
		ft_putendl_fd(s, here[index].pipe[1]);
		free(s);
	}
	close_fd(&here[index].pipe[1]);
	close_fd(&here[index].pipe[0]);
	return (NULL);
}
