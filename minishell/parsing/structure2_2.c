/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure2_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 22:36:33 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:29:53 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab2(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j] != NULL)
		{
			free(tab[i][j]);
			j++;
		}
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab(char ***tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	nb_cmd(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp && (tmp->token != PIPE))
	{
		if (tmp->token == CMD && tmp->content[0] != '\0')
			i++;
		tmp = tmp->next;
	}
	return (i);
}
