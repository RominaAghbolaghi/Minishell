/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:21:00 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/07 15:35:54 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_data			*data;

	if (ac != 1)
		return (0);
	(void)av;
	data = init_data(env);
	while (1)
	{
		handle_signal();
		line = readline("minihell-66.6$ ");
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		if (!*line || !env[0])
			continue ;
		data->envi = env2(data->env_list);
		add_history(line);
		if (verif_quote(line, data) <= 0)
			exec_loop(data, line);
		data->w++;
		free_tab1(data->envi);
		free(line);
	}
	free_data(data);
}
