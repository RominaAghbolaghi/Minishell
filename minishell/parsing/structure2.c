/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 23:15:21 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:30:02 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew2(t_data *data, char content, int i)
{
	t_list	*element;

	element = malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->content = c_to_str(content);
	element->next = NULL;
	element->prev = NULL;
	element->token = get_token2(element->content);
	element->data = data;
	element->indice = i;
	return (element);
}

void	creat_list2(char *str, t_data *dbl_list, t_list **first, t_list **last)
{
	int		i;
	int		j;
	t_list	*list;

	j = 0;
	i = 0;
	if (!str)
		return ;
	*first = ft_lstnew2(dbl_list, str[i], j);
	list = *first;
	while (str[++i] != '\0')
		*last = ft_lstadd_back(&list, ft_lstnew2(dbl_list, str[i], ++j));
	if (ft_strlen(str) == 1)
		*last = *first;
}

void	join_link2(t_list **first, t_list **last)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *first;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			if (tmp->token == tmp->next->token && tmp->token != SIMPLE_QUOTE
				&& tmp->token != DOUBLE_QUOTE)
			{
				tmp->content = ft_strjoin_bis(tmp->content, tmp->next->content);
				tmp2 = tmp->next;
				tmp->next = tmp->next->next;
				if (tmp2->next != NULL)
					tmp2->next->prev = tmp;
				else
					*last = tmp;
				free(tmp2);
			}
			else
					tmp = tmp->next;
		}
	}
}

char	***tab_cmd(t_data *dbl_list)
{
	int		i;
	char	***tab;
	t_list	*tmp;

	i = 1;
	tmp = dbl_list->first;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
			i++;
		tmp = tmp->next;
	}
	dbl_list->nb_cmd = i;
	tab = malloc(sizeof(char **) * (i + 1));
	if (!tab)
		return (NULL);
	tmp = dbl_list->first;
	i = 0;
	while (tmp != NULL)
	{
		if (sub_tab_cmd(&tmp, &tab, &i) == -1)
			return (NULL);
	}
	tab[i] = NULL;
	return (tab);
}

int	sub_tab_cmd(t_list **tmp, char ****tab, int *i)
{
	int	k;
	int	j;

	j = 0;
	k = nb_cmd(*tmp);
	(*tab)[*i] = malloc(sizeof(char *) * (k + 1));
	if (!(*tab)[*i])
		return (free_tab(*tab), -1);
	while (*tmp != NULL && (*tmp)->token != PIPE)
	{
		if ((*tmp)->token == CMD && (*tmp)->content[0] != '\0')
		{
			(*tab)[*i][j] = ft_strdup((*tmp)->content);
			if (!(*tab)[*i][j])
				return (free_tab2(*tab), -1);
			j++;
		}
		(*tmp) = (*tmp)->next;
	}
	(*tab)[*i][j] = NULL;
	if ((*tmp) != NULL)
		*tmp = (*tmp)->next;
	(*i)++;
	return (0);
}
