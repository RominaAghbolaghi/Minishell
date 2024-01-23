/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:30:09 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:28:59 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_dollar_sub(t_list **lst, t_list *tmp)
{
	char	*str;

	tmp = (*lst)->next;
	del_link((*lst));
	(*lst) = tmp;
	if (ft_isalpha((*lst)->content[0]) == 1
		|| (*lst)->content[0] == '_')
	{
		str = get_path_var((*lst)->data->env_list, (*lst)->content, 0);
		if (str == NULL)
			(*lst)->content = (replace_alpha_null2((*lst)));
		else
		{
			(*lst)->content = (replace_alpha_env2((*lst), str));
			integration(lst);
		}
	}
	else if ((*lst)->content[0] == '?')
	{
		(*lst)->content = replace_dollar_return_code2((*lst));
		(*lst)->token = ALPHANUMERIC;
	}
	else if (ft_isdigit((*lst)->content[0]) == 1)
		(*lst)->content = replace_dollar_digit2((*lst));
}

void	replace_dollar_sub2(t_list **lst, t_list *tmp)
{
	if ((*lst)->next && ((*lst)->next->token == ALPHANUMERIC
			|| (*lst)->next->token == INTERRO))
	{
		if (ft_isalnum((*lst)->next->content[0]) == 1
			|| (*lst)->next->content[0] == '_'
			|| (*lst)->next->content[0] == '?')
			replace_dollar_sub(lst, tmp);
		else
			(*lst)->token = ALPHANUMERIC;
	}
	else
	(*lst)->token = ALPHANUMERIC;
}
