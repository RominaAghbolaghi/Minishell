/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:17:43 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:29:09 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_token_type(t_list *tmp)
{
	while (tmp && tmp->next != NULL)
	{
		if (tmp->next->next && tmp->next->token == SPACES)
		{
			if (tmp->token == FILE_IN && tmp->next->next->token == ALPHANUMERIC)
				tmp->next->next->token = OPEN_FILE;
			else if (tmp->token == FILE_OUT
				&& tmp->next->next->token == ALPHANUMERIC)
				tmp->next->next->token = EXIT_FILE;
			else if (tmp->token == FILE_OUT_SUR
				&& tmp->next->next->token == ALPHANUMERIC)
				tmp->next->next->token = EXIT_FILE_RET;
			else if (tmp->token == HERE_DOC
				&& tmp->next->next->token == ALPHANUMERIC)
				tmp->next->next->token = LIMITOR;
		}
		tmp = tmp->next;
	}
}

void	join_link(t_data *data)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = data->first;
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
					data->last = tmp;
				free(tmp2);
			}
			else
					tmp = tmp->next;
		}
	}
}
