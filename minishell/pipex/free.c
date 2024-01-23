/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 02:28:36 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 15:37:06 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab1(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}

void	free_all_data(t_data *data, int code, int code2)
{
	if (code2 < 4)
		perror(" ");
	if (code2 > 0)
		free_tab1(data->exec->path);
	if (code2 > 2)
		free(data->exec->pids);
	exit(code);
}

void	free_data(t_data *data)
{
	if (data->w == 0)
	{
		free_list(data->first);
		free_tab2(data->tb_cmd);
		free_tab1(data->envi);
	}
	free_list_env(data->env_list);
	printf("exit\n");
}
