/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:18:06 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/06 15:35:46 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*starton(void)
{
	static t_data	data;

	return (&data);
}

void	exec_loop(t_data *data, char*line)
{
	ft_negative(line);
	creat_list(line, data);
	join_link(data);
	if (syntax_error(data) == 0)
	{
		check_quotes_loop(data, line);
		if (data->tb_cmd[0] != NULL && data->tb_cmd
			&& data->tb_cmd[0][0] && data->here_status == 0)
			loop_cmd(data);
		else
			free_data_loop(data);
		data->here_status = 0;
		free_tab2(data->tb_cmd);
	}		
	if (data->first != NULL)
		free_list(data->first);
}

void	handle_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
}

t_data	*init_data(char **env)
{
	t_data	*data;

	data = starton();
	ft_memset(data, 0, sizeof(t_data));
	data->env_list = creat_env_lst(env);
	data->n = 1;
	return (data);
}
