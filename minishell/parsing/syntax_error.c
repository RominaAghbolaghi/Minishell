/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:28:13 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:30:19 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error(t_data *data)
{
	t_list	*tmp;

	tmp = data->first;
	while (tmp != NULL)
	{
		if (verif_pipe(tmp) == 1)
			return (data->exit_code = 2, 2);
		if (verif_spaces_chevron(tmp) == 1)
			return (data->exit_code = 2, 2);
		if (str_syntax_error_checking(data, tmp) == 2)
			return (2);
		if (verif_chev_next_chev(tmp) == 1)
			return (data->exit_code = 2, 2);
		tmp = tmp->next;
	}
	return (0);
}

int	verif_spaces_chevron(t_list *tmp)
{
	if ((tmp->token == REDIRECTION_IN || tmp->token == REDIRECTION_OUT)
		&& tmp->next != NULL && tmp->next->next != NULL
		&& tmp->next->token == SPACES
		&& tmp->next->next->token == REDIRECTION_IN)
	{
		if (ft_strlen(tmp->content) <= 4)
			return (ft_printf_fd(2, IN_REDICT_ERROR), 1);
		else if (ft_strlen(tmp->content) == 5)
			return (ft_printf_fd(2, HERE_DOC_ERROR), 1);
		else if (ft_strlen(tmp->content) > 5)
			return (ft_printf_fd(2, TRIPLE_IN_CHEVRON_ERROR), 1);
	}
	if ((tmp->token == REDIRECTION_IN || tmp->token == REDIRECTION_OUT)
		&& tmp->next != NULL && tmp->next->next != NULL
		&& tmp->next->token == SPACES
		&& tmp->next->next->token == REDIRECTION_OUT)
	{
		if (ft_strlen(tmp->content) <= 4)
			return (ft_printf_fd(2, OUT_REDICT_ERROR), 1);
		else if (ft_strlen(tmp->content) == 5)
			return (ft_printf_fd(2, OUT_APPEND_ERROR), 1);
		else if (ft_strlen(tmp->content) > 5)
			return (ft_printf_fd(2, TRIPLE_OUT_CHEVRON_ERROR), 1);
	}
	return (0);
}

int	verif_chev_next_chev(t_list *tmp)
{
	if (tmp->token == REDIRECTION_IN)
	{
		if (tmp->next->token == REDIRECTION_OUT
			&& ft_strlen(tmp->next->content) == 1)
			return (ft_printf_fd(2, OUT_REDICT_ERROR), 1);
		else if (tmp->next->token == REDIRECTION_OUT
			&& ft_strlen(tmp->next->content) > 1)
			return (ft_printf_fd(2, OUT_APPEND_ERROR), 1);
	}
	else if (tmp->token == REDIRECTION_OUT)
	{
		if (tmp->next->token == REDIRECTION_IN
			&& ft_strlen(tmp->next->content) == 1)
			return (ft_printf_fd(2, IN_REDICT_ERROR), 1);
		else if (tmp->next->token == REDIRECTION_IN
			&& ft_strlen(tmp->next->content) > 1)
			return (ft_printf_fd(2, HERE_DOC_ERROR), 1);
	}
	return (0);
}

int	verif_pipe(t_list *tmp)
{
	if (tmp->token == PIPE
		&& (tmp->prev == NULL
			|| (tmp->prev->token == SPACES && tmp->prev->prev == NULL)))
		return (ft_printf_fd(2, PIPE_ERROR), 1);
	else if ((tmp->token == PIPE) && ((tmp->prev->token == REDIRECTION_IN
				|| tmp->prev->token == REDIRECTION_OUT)
			|| ((tmp->prev->token == SPACES)
				&& (tmp->prev->prev->token == REDIRECTION_IN
					|| tmp->prev->prev->token == REDIRECTION_OUT))))
		return (ft_printf_fd(2, PIPE_ERROR), 1);
	else if (tmp->token == PIPE && ft_strlen(tmp->content) > 1)
		return (ft_printf_fd(2, PIPE_ERROR), 1);
	else if (tmp->token == PIPE && (tmp->next == NULL
			|| (tmp->next->token == SPACES && tmp->next->next == NULL)))
		return (ft_printf_fd(2, PIPE_ERROR), 1);
	else if (tmp->token == PIPE && tmp->next != NULL
		&& tmp->next->token == SPACES && tmp->next->next->token == PIPE)
		return (ft_printf_fd(2, PIPE_ERROR), 1);
	else
		return (0);
}

void	check_quotes_loop(t_data *data, char *line)
{
	char	*str;

	str = ft_strdup(line);
	ft_positive(data);
	replace_quote(data);
	replace_dollar(data);
	join_link(data);
	get_token3(&data->first);
	get_token4(&data->first);
	get_token5(&data->first);
	data->tb_cmd = tab_cmd(data);
	init(data);
	here_doc(data, str);
	free(str);
}
