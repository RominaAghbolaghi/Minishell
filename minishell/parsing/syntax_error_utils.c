/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:46:19 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:30:10 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_syntax_error_checking(t_data *data, t_list *tmp)
{
	if (tmp->token == REDIRECTION_IN && ft_strlen(tmp->content) == 3)
		return (data->exit_code = 2, ft_printf_fd(2, IN_REDICT_ERROR), 2);
	else if (tmp->token == REDIRECTION_IN && ft_strlen(tmp->content) > 3)
		return (data->exit_code = 2, ft_printf_fd(2, HERE_DOC_ERROR), 2);
	else if (tmp->token == REDIRECTION_IN && ft_strlen(tmp->content) < 3
		&& (tmp->next == NULL
			|| (tmp->next->token == SPACES && tmp->next->next == NULL)))
		return (data->exit_code = 2, ft_printf_fd(2, NEWLINE_ERROR), 2);
	if (tmp->token == REDIRECTION_OUT && ft_strlen(tmp->content) == 3)
		return (data->exit_code = 2, ft_printf_fd(2, OUT_REDICT_ERROR), 2);
	else if (tmp->token == REDIRECTION_OUT && ft_strlen(tmp->content) > 3)
		return (data->exit_code = 2, ft_printf_fd(2, OUT_APPEND_ERROR), 2);
	else if (tmp->token == REDIRECTION_OUT && ft_strlen(tmp->content) < 3
		&& (tmp->next == NULL
			|| (tmp->next->token == SPACES && tmp->next->next == NULL)))
		return (data->exit_code = 2, ft_printf_fd(2, NEWLINE_ERROR), 2);
	return (0);
}
