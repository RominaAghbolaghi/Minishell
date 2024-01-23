/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:01:28 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/07 14:38:46 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_verif_built(char **cmds, t_data *data)
{
	if (ft_strcmp(cmds[0], "echo") == 0)
		return (echo(cmds), -42);
	else if (ft_strcmp(cmds[0], "cd") == 0)
	{
		if (cd(cmds, data) == 0)
			return (-42);
		else
			return (1);
	}
	else if (ft_strcmp(cmds[0], "pwd") == 0)
		return (pwd(), -42);
	else if (ft_strcmp(cmds[0], "export") == 0)
	{
		return (export(cmds, data));
	}
	else if (ft_strcmp(cmds[0], "unset") == 0)
		return (unset(cmds, data, 0, 0), -42);
	else if (ft_strcmp(cmds[0], "env") == 0)
		return (env_builtin(data->envi), -42);
	else if (ft_strcmp(cmds[0], "exit") == 0)
		return (exit_builtin(cmds, data, 1), -42);
	else
		return (-1);
}

void	ft_verif_built2(char **cmds, t_data *data)
{
	if (ft_strcmp(cmds[0], "cd") == 0)
		cd2(cmds, data);
	else if (ft_strcmp(cmds[0], "export") == 0)
		return (export2(cmds, data));
	else if (ft_strcmp(cmds[0], "exit") == 0)
		exit_builtin(cmds, data, 0);
	else if (ft_strcmp(cmds[0], "unset") == 0)
		unset(cmds, data, 0, 0);
	else
		return ;
}
