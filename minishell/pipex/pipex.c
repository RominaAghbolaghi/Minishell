/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:11:49 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 14:09:14 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_all_child(t_data *data, int i)
{
	close_fd(&data->exec->prev);
	while (++i < data->nb_cmd)
	{
		waitpid(data->exec->pids[i], &data->exit_code, 0);
		if (WIFEXITED(data->exit_code))
			data->exit_code = WEXITSTATUS(data->exit_code);
		if (WIFSIGNALED(data->exit_code))
		{
			data->exit_code = WTERMSIG(data->exit_code);
			if (data->exit_code == 2 || data->exit_code == 3)
				data->exit_code += 128;
		}
		if (data->exit_code == 131)
			ft_printf_fd(2, "^'\\'Quit (core dumped)\n");
	}
	free_tab1(data->exec->path);
	free(data->exec->pids);
	free(data->exec);
	i = 0;
	while (i < data->nb_here)
		free(data->here[i++].delim);
	if (data->nb_here > 0)
		free(data->here);
}

void	close_all_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_here)
	{
		close_fd(&data->here[i].pipe[0]);
		i++;
	}
}

void	handle_parent_process(t_data *data, int i)
{
	signal(SIGQUIT, ctrlc_2);
	if (data->nb_cmd == 1)
		ft_verif_built2(data->tb_cmd[i], data);
	close_fd(&data->exec->fd[1]);
	close_fd(&data->exec->prev);
	data->exec->prev = data->exec->fd[0];
	close_all_pipes(data);
}

void	loop_cmd(t_data *data)
{
	int		i;
	t_list	*tmp;

	tmp = data->first;
	data->exec->prev = -1;
	i = 0;
	signal(SIGINT, ctrlc_2);
	while (i < data->nb_cmd)
	{
		data->exec->j = i;
		if (pipe(data->exec->fd) == -1)
			free_all_data(data, 1, i);
		data->exec->pids[i] = fork();
		if (data->exec->pids[i] == -1)
			free_all_data(data, 1, i);
		if (data->exec->pids[i] == 0)
			child_process_2(data, data->tb_cmd, i, &tmp);
		else
			handle_parent_process(data, i);
		i++;
	}
	wait_all_child(data, -1);
}

void	exec_cmd(t_data *data)
{
	if (data->exec->cmdpath != NULL)
	{
		execve(data->exec->cmdpath, data->exec->cmds, data->envi);
		if (ft_strcmp(data->exec->cmds[0], ".") == 0)
			ft_putendl_fd(" .: filename argument required", 2);
		else if (ft_strcmp(data->exec->cmds[0], "..") == 0)
			ft_putendl_fd(" ..: command not found", 2);
		else
		{
			ft_putchar_fd(' ', 2);
			ft_putendl_fd(strerror(errno), 2);
		}
		free(data->exec->cmdpath);
	}
	free_data_2_and_exit(data, 127);
}
