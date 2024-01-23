/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:26:37 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:32:48 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	if (close(*fd) != 0)
		perror("Close");
	*fd = -1;
}

void	close_pipes(t_data *data)
{
	if ((data->exec->j) < data->nb_cmd - 1)
		close_fd(&data->exec->fd[0]);
	close_fd(&data->exec->fd[1]);
}

void	child_process_2(t_data *data, char ***cmds, int i, t_list **tmp)
{
	int	j;
	int	ex;

	j = 0;
	ex = 0;
	data->n = data->n + 1;
	signal(SIGINT, &antislash);
	signal(SIGQUIT, &antislash);
	while ((*tmp) && j < i)
	{
		if ((*tmp)->token == PIPE)
			j++;
		(*tmp) = (*tmp)->next;
	}
	redirect(data);
	redirect2(data, *tmp);
	data->exec->cmds = cmds[i];
	ex = ft_verif_built(data->exec->cmds, data);
	if (ex == -42)
		free_data_2_and_exit(data, 0);
	if (ex == 1)
		free_data_2_and_exit(data, 1);
	data->exec->cmdpath = access_check(data->exec->path, data->exec->cmds[0]);
	exec_cmd(data);
}

int	init(t_data *data)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec) * 1);
	if (!exec)
	{
		perror("Erreur d'allocation de mémoire");
		free(exec);
		exit(1);
	}
	exec->path = get_paths_from_environment(get_path_var1(data->envi));
	if (exec->path == NULL)
	{
		return (data->exit_code = 0, 0);
	}
	exec->j = 0;
	exec->pids = ft_calloc(sizeof(int), data->nb_cmd + 1);
	if (exec->pids == NULL)
	{
		perror("Erreur d'allocation de mémoire");
		free_tab1(data->exec->path);
		free(exec);
		exit(1);
	}
	data->exec = exec;
	return (1);
}
