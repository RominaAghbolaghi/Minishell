/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:12:36 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/06 15:38:40 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_env(char *var_name, char **env)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(var_name);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
			return (env[i] + len + 1);
	}
	return (NULL);
}

char	*trim_path(char *path)
{
	int	i;
	int	len;

	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '/')
		len --;
	i = len - 1;
	while (i >= 0)
	{
		if (path[i] == '/')
		{
			if (i == 0)
				path[i + 1] = 0;
			else
				path[i] = 0;
			break ;
		}
		i--;
	}
	return (path);
}

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	sub_cd(t_data *data, char *cmd)
{
	char	*env_var;
	char	*str;

	str = ft_strjoin(ft_get_env("PWD", data->envi), "/");
	env_var = ft_strjoin(str, cmd);
	modif_env(data, env_var);
	free(str);
	free(env_var);
}

int	is_builtin(char **cmds)
{
	if (ft_strcmp(cmds[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(cmds[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(cmds[0], "env") == 0)
		return (0);
	else if (ft_strcmp(cmds[0], "exit") == 0)
		return (0);
	else if (ft_strcmp(cmds[0], "export") == 0)
		return (0);
	else if (ft_strcmp(cmds[0], "pwd") == 0)
		return (0);
	return (1);
}
