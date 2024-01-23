/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:53:30 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/07 15:05:30 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*return_link_by_str(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, str, ft_strlen(str)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*ft_lstnew_env(void *content)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

int	pop_node(t_env **head, t_env *to_remove)
{
	t_env	*current;

	if (!head || !*head || !to_remove)
		return (0);
	current = *head;
	if (*head == to_remove)
	{
		*head = current->next;
		return (ft_lstdelone_env(to_remove, &free), 0);
	}
	while (current->next && current->next != to_remove)
		current = current->next;
	if (current->next != to_remove)
		return (0);
	current->next = to_remove->next;
	return (ft_lstdelone_env(to_remove, &free), 1);
}

int	unset_end(t_data *data)
{
	free_tab1(data->envi);
	data->envi = env2(data->env_list);
	return (0);
}

int	unset(char **cmd, t_data *data, int i, int j)
{
	t_env	*env_lst;

	if (!cmd[1])
		return (0);
	while (cmd[++i])
	{
		env_lst = data->env_list;
		while (env_lst)
		{
			if (var_env_len(cmd[i]) != ft_strlen(cmd[i]))
				break ;
			if (ft_strlen(cmd[i]) > var_env_len(env_lst->content))
				j = ft_strlen(cmd[i]);
			else
				j = var_env_len(env_lst->content);
			if (!ft_strncmp(env_lst->content, cmd[i], j))
			{
				pop_node(&data->env_list, return_link_by_str(env_lst, cmd[i]));
				break ;
			}
			env_lst = env_lst->next;
		}
	}
	return (unset_end(data));
}
