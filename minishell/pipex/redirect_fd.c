/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:27:00 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:33:08 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	getpipe(t_here *here, t_data *data, char *file)
{
	int	i;

	i = 0;
	while (i < data->nb_here)
	{
		if (!ft_strcmp(here[i].delim, file))
			return (here[i].pipe[0]);
		close(here[i].pipe[0]);
		i++;
	}
	return (-1);
}

void	redirect(t_data *data)
{
	if (data->exec->j != 0)
	{
		dup2(data->exec->prev, STDIN_FILENO);
		close_fd(&data->exec->prev);
	}
	if (data->exec->j != data->nb_cmd - 1)
		dup2(data->exec->fd[1], STDOUT_FILENO);
	close_fd(&data->exec->fd[1]);
	close_fd(&data->exec->fd[0]);
}

int	open_file2(int fd, t_list *tmp, t_data *data)
{
	if (tmp->token == EXIT_FILE)
		fd = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (tmp->token == EXIT_FILE_RET)
		fd = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (tmp->token == OPEN_FILE)
		fd = open(tmp->content, O_RDONLY);
	else if (tmp->token == LIMITOR)
		fd = getpipe(data->here, data, tmp->content);
	return (fd);
}

int	redirect2(t_data *data, t_list *tmp1)
{
	t_list	*tmp;
	int		fd;

	tmp = tmp1;
	while (tmp != NULL && tmp->token != PIPE)
	{
		if (tmp->token == EXIT_FILE || tmp->token == EXIT_FILE_RET
			|| tmp->token == OPEN_FILE || tmp->token == LIMITOR)
		{
			fd = open_file2(fd, tmp, data);
			if (fd == -1)
			{
				perror(tmp->content);
				free_data_2_and_exit(data, 1);
			}
			if (tmp->token == EXIT_FILE || tmp->token == EXIT_FILE_RET)
				dup2(fd, STDOUT_FILENO);
			else
				dup2(fd, STDIN_FILENO);
			close(fd);
		}
		tmp = tmp->next;
	}
	return (0);
}
