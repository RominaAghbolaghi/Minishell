/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:51:16 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/08 10:05:43 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_to_many(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (i >= 2)
			return (1);
	return (0);
}

int	cd_home(char **cmd, char **env, t_data *data)
{
	char	*env_var;

	env_var = ft_get_env("HOME", env);
	if (!env_var)
		return (ft_printf_fd(2, ERR_CD_HOME, cmd[1]), 0);
	if (chdir(env_var) == -1)
		return (ft_printf_fd(2, ERR_CD, env_var, 0));
	else
		modif_env(data, env_var);
	return (1);
}

int	cd_minus(char **cmd, char **env, t_data *data)
{
	char	*env_var;

	env_var = ft_get_env("OLDPWD", env);
	if (!env_var)
		return (ft_printf_fd(2, ERR_CD_OPWD, cmd[1]), 0);
	if (chdir(env_var) == -1)
		return (ft_printf_fd(2, ERR_CD, cmd[1]), 0);
	else
		modif_env(data, env_var);
	return (1);
}

int	cd_point_point(t_data *data)
{
	char	*env_var;

	env_var = trim_path(getcwd(NULL, 0));
	if (!env_var)
		return (ft_printf_fd(2, ERR_PWD), 0);
	if (chdir(env_var) == -1)
	{
		free(env_var);
		return (0);
	}
	else
		modif_env(data, env_var);
	free(env_var);
	return (1);
}

int	cd(char **cmd, t_data *data)
{
	if (cd_to_many(cmd))
		return (ft_printf_fd(2, ERR_CD_MANY), 1);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
	{
		if (!cd_home(cmd, data->envi, data))
			return (1);
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		if (!cd_minus(cmd, data->envi, data))
			return (1);
	}
	else if (!ft_strcmp(cmd[1], ".."))
	{	
		if (cd_point_point(data))
			return (0);
	}
	else if (chdir(cmd[1]) == -1)
		return (ft_printf_fd(2, ERR_CD, cmd[1]), 1);
	else
		sub_cd(data, cmd[1]);
	return (0);
}
