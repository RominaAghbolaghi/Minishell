/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:45:19 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:30:41 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*replace_single_quotes(t_list *tmp, int *i)
{
	t_list	*tmp2;

	if (tmp->prev != NULL && tmp->prev->token == DOLLAR)
		tmp->prev->indice = -1;
	if (tmp->next && tmp->next->token == ALPHANUMERIC)
	{
		tmp2 = tmp->next;
		del_link(tmp);
		tmp = tmp2;
		del_link(tmp->next);
	}
	else if (tmp->next && tmp->next->token == SIMPLE_QUOTE)
	{
		tmp2 = tmp->next;
		del_link(tmp);
		tmp = tmp2;
		tmp2 = tmp->next;
		del_link(tmp);
		tmp = tmp2;
		*i = 1;
	}
	return (tmp);
}

t_list	*replace_double_quotes(t_list *tmp, int *i)
{
	t_list	*tmp2;

	if (tmp->prev != NULL && tmp->prev->token == DOLLAR)
		tmp->prev->indice = -1;
	if (tmp->next && tmp->next->token == ALPHANUMERIC)
	{
		tmp2 = tmp->next;
		del_link(tmp);
		tmp = tmp2;
		replace_dollar_quote(tmp);
		del_link(tmp->next);
	}
	else if (tmp->next && tmp->next->token == DOUBLE_QUOTE)
	{
		tmp2 = tmp->next;
		del_link(tmp);
		tmp = tmp2;
		tmp2 = tmp->next;
		del_link(tmp);
		tmp = tmp2;
		*i = 1;
	}
	return (tmp);
}
