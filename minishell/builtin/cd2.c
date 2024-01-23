/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:31:47 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/06 13:23:07 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_home2(char **cmd, char **env, t_data *data)
{
	char	*env_var;

	(void)cmd;
	env_var = ft_get_env("HOME", env);
	if (!env_var)
		return (0);
	if (chdir(env_var) == -1)
		return (0);
	else
		modif_env(data, env_var);
	return (1);
}

int	cd_minus2(char **cmd, char **env, t_data *data)
{
	char	*env_var;

	(void)cmd;
	env_var = ft_get_env("OLDPWD", env);
	if (!env_var)
		return (0);
	if (chdir(env_var) == -1)
		return (0);
	else
		modif_env(data, env_var);
	return (1);
}

int	cd_point_point2(t_data *data)
{
	char	*env_var;

	env_var = trim_path(getcwd(NULL, 0));
	if (!env_var)
		return (0);
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

int	cd2(char **cmd, t_data *data)
{
	if (cd_to_many(cmd))
		return (1);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
	{
		if (!cd_home2(cmd, data->envi, data))
			return (1);
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		if (!cd_minus2(cmd, data->envi, &*data))
			return (1);
	}
	else if (!ft_strcmp(cmd[1], ".."))
	{
		if (cd_point_point2(data))
			return (0);
	}
	else if (chdir(cmd[1]) == -1)
		return (1);
	else
		sub_cd(data, cmd[1]);
	return (0);
}

void	modif_env(t_data *data, char *new_pwd)
{
	char	*str;
	t_env	*tmp;

	tmp = data->env_list;
	str = ft_get_env("PWD", data->envi);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "PWD=", 4) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strjoin("PWD=", new_pwd);
		}
		if (ft_strncmp(tmp->content, "OLDPWD=", 7) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strjoin("OLDPWD=", str);
		}
		tmp = tmp->next;
	}
}
