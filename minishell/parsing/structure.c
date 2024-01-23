/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 23:15:21 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:29:42 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(t_data *data, char content, int i)
{
	t_list	*element;

	element = malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->content = c_to_str(content);
	element->next = NULL;
	element->prev = NULL;
	element->token = get_token(element->content);
	element->data = data;
	element->indice = i;
	return (element);
}

t_list	*ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return (NULL);
	}
	if (lst == NULL || new == NULL)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
	return (new);
}

void	creat_list(char *str, t_data *dbl_list)
{
	int		i;
	int		j;
	t_list	*list;

	j = 0;
	i = 0;
	if (!str)
		return ;
	dbl_list->first = ft_lstnew(dbl_list, str[i], j);
	list = dbl_list->first;
	while (str[++i] != '\0')
		dbl_list->last = ft_lstadd_back(&list,
				ft_lstnew(dbl_list, str[i], ++j));
	if (ft_strlen(str) == 1)
		dbl_list->last = dbl_list->first;
}

char	*c_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	del_link(t_list *lst)
{
	if (lst == NULL)
		return ;
	if (lst->prev != NULL)
		lst->prev->next = lst->next;
	else
		lst->data->first = lst->next;
	if (lst->next != NULL)
		lst->next->prev = lst->prev;
	else
		lst->data->last = lst->prev;
	free(lst->content);
	free(lst);
}
