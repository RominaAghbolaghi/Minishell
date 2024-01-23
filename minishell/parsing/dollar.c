/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:53:17 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:28:39 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_dollar(t_data *data)
{
	t_list	*lst;
	t_list	*tmp;

	lst = data->first;
	while (lst)
	{
		if (lst->indice == -1)
		{
			tmp = lst->next;
			del_link(lst);
			lst = tmp;
		}
		else if (lst->token == DOLLAR)
			replace_dollar_sub2(&lst, tmp);
		if (lst)
			lst = lst->next;
	}
}

char	*replace_dollar_alpha2(t_list *lst)
{
	char	*str;

	str = get_path_var(lst->data->env_list, lst->content, 0);
	if (str == NULL)
		return (replace_alpha_null(lst, 0));
	else
		return (replace_alpha_env(lst, str, 0));
}

char	*replace_dollar_digit2(t_list *lst)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * ft_strlen(lst->content));
	if (ft_isdigit(lst->content[i]) == 1)
			i = i + 1;
	while (lst->content[i])
	{
		str[j] = lst->content[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free (lst->content);
	return (str);
}

char	*replace_dollar_return_code2(t_list *lst)
{
	int		i;
	int		j;
	int		k;
	char	*str;
	char	*tmp;

	i = 0;
	j = -1;
	k = -1;
	tmp = ft_itoa(lst->data->exit_code);
	str = calloc(sizeof(char), (ft_strlen(lst->content) + ft_strlen(tmp)));
	while (lst->content[i])
	{
		if (lst->content[i] == '?')
		{
			i = i + 1;
			while (tmp[++k])
				str[++j] = tmp[k];
			str[++j] = lst->content[i];
		}
		else
			str[++j] = lst->content[i++];
	}
	return (free(tmp), free(lst->content), str);
}

void	integration(t_list **lst)
{
	t_list	*first;
	t_list	*last;

	first = NULL;
	last = NULL;
	creat_list2((*lst)->content, (*lst)->data, &first, &last);
	free((*lst)->content);
	join_link2(&first, &last);
	if ((*lst)->prev == NULL)
		(*lst)->data->first = first;
	else
	{
		(*lst)->prev->next = first;
		first->prev = (*lst)->prev;
	}
	if ((*lst)->next == NULL)
		(*lst)->data->last = last;
	else
	{
		(*lst)->next->prev = last;
		last->next = (*lst)->next;
	}
	free((*lst));
	*lst = last;
}
