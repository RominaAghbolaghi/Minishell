/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:53:04 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/06 13:24:17 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_export(char *new_export_var)
{
	int		i;
	char	**new_var;

	if (new_export_var[0] == '=')
		return (1);
	new_var = ft_split(new_export_var, '=');
	i = -1;
	if (!new_var[0] || ft_strlen(new_var[0]) >= 50)
		return (free_tab1(new_var), 1);
	if (!ft_strcmp(new_var[0], "$?"))
		return (free_tab1(new_var), 0);
	if (ft_isalpha(new_var[0][0]) == 0 && new_var[0][0] != '_')
	{
		if (ft_isdigit(new_var[0][0]))
			return (free_tab1(new_var), 1);
	}
	while (new_var[0][++i])
	{
		if (!ft_isalpha(new_var[0][i]) && new_var[0][i] != '_'
			&& !ft_isdigit(new_var[0][i]))
			return (free_tab1(new_var), 1);
	}
	return (free_tab1(new_var), 0);
}

int	add_to_env(char *cmd, t_env **envi)
{
	ft_envadd_back(envi, ft_envnew(cmd));
	return (1);
}

int	update_env(char *cmd, t_env **envi)
{
	char	**var;
	char	**var2;
	t_env	*tmp;

	tmp = *envi;
	var = ft_split(cmd, '=');
	while (tmp != NULL)
	{
		var2 = ft_split(tmp->content, '=');
		if (!ft_strcmp(var2[0], var[0]))
		{
			if (!ft_strchr(cmd, '='))
				return (free_tab1(var), free_tab1(var2), 0);
			free(tmp->content);
			tmp->content = ft_strdup(cmd);
			if (!tmp->content)
				return (free_tab1(var), free_tab1(var2), 0);
			return (free_tab1(var), free_tab1(var2), 0);
		}
		free_tab1(var2);
		tmp = tmp->next;
	}
	add_to_env(cmd, envi);
	return (free_tab1(var), 0);
}

int	export(char **cmd, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	j = -42;
	if (!cmd[1])
		return (export_noargs(data->envi), 1);
	while (cmd[i])
	{
		if (parse_export(cmd[i]))
		{
			ft_printf_fd(2, ERR_EXP_PARSE, cmd[i]);
			i++;
			j = 1;
			continue ;
		}
		update_env(cmd[i], &data->env_list);
		i++;
	}
	free_tab1(data->envi);
	data->envi = env2(data->env_list);
	return (j);
}

void	update_lst_env(char *cmd, t_env **env, char **var)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, var[0], ft_strlen(var[0])))
		{
			free(tmp->content);
			tmp->content = ft_strdup(cmd);
		}
		tmp = tmp->next;
	}
}
