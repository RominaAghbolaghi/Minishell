/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:58:40 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/07 15:40:43 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	free_list_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env->next;
		free(env->content);
		free(env);
		env = tmp;
	}
}

void	free_data_2_and_exit(t_data *data, int code)
{
	int	i;

	i = 0;
	close_fd(&data->exec->fd[0]);
	close_fd(&data->exec->fd[1]);
	free_tab1(data->exec->path);
	free(data->exec->pids);
	free(data->exec);
	if (data->tb_cmd[0])
		free_tab2(data->tb_cmd);
	if (data->first != NULL)
		free_list(data->first);
	free_list_env(data->env_list);
	free_tab1(data->envi);
	i = 0;
	while (i < data->nb_here)
		free(data->here[i++].delim);
	if (data->nb_here > 0)
		free(data->here);
	exit(code);
}

void	free_data_2(t_data *data)
{
	int	i;

	i = 0;
	free_tab1(data->exec->path);
	free(data->exec->pids);
	free(data->exec);
	if (data->tb_cmd[0])
		free_tab2(data->tb_cmd);
	if (data->first != NULL)
		free_list(data->first);
	free_list_env(data->env_list);
	free_tab1(data->envi);
	i = 0;
	while (i < data->nb_here)
	{
		free(data->here[i].delim);
		i++;
	}
	if (data->nb_here > 0)
		free(data->here);
}

void	free_data_loop(t_data *data)
{
	int	i;

	i = -1;
	free_tab1(data->exec->path);
	free(data->exec->pids);
	free(data->exec);
	while (++i < data->nb_here)
		free(data->here[i].delim);
	close_all_pipes(data);
	if (data->nb_here > 0)
		free(data->here);
}
