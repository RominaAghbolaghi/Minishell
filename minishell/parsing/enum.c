/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:11:36 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:29:18 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	get_token(char *str)
{
	if (str[0] == '$')
		return (DOLLAR);
	else if (str[0] == '|')
		return (PIPE);
	else if (str[0] == '<')
		return (REDIRECTION_IN);
	else if (str[0] == '>')
		return (REDIRECTION_OUT);
	else if (str[0] == '?')
		return (INTERRO);
	else if (str[0] == '\'')
		return (SIMPLE_QUOTE);
	else if (str[0] == '\"')
		return (DOUBLE_QUOTE);
	else if (str[0] == ' ' || str[0] == '\t')
		return (SPACES);
	else
		return (ALPHANUMERIC);
}

t_tokens	get_token2(char *str)
{
	if (str[0] == ' ' || str[0] == '\t')
		return (SPACES);
	else
		return (ALPHANUMERIC);
}

void	get_token3(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp && tmp->next != NULL)
	{
		if (tmp->token == REDIRECTION_IN && strlen(tmp->content) == 1)
			tmp->token = FILE_IN;
		else if (tmp->token == REDIRECTION_OUT && strlen(tmp->content) == 1)
			tmp->token = FILE_OUT;
		else if (tmp->token == REDIRECTION_OUT && strlen(tmp->content) == 2)
			tmp->token = FILE_OUT_SUR;
		else if (tmp->token == REDIRECTION_IN && strlen(tmp->content) == 2)
			tmp->token = HERE_DOC;
		tmp = tmp->next;
	}
}

void	get_token4(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp && tmp->next != NULL)
	{
		if (tmp->next)
		{
			if (tmp->token == FILE_IN && tmp->next->token == ALPHANUMERIC)
				tmp->next->token = OPEN_FILE;
			else if (tmp->token == FILE_OUT && tmp->next->token == ALPHANUMERIC)
				tmp->next->token = EXIT_FILE;
			else if (tmp->token == FILE_OUT_SUR
				&& tmp->next->token == ALPHANUMERIC)
				tmp->next->token = EXIT_FILE_RET;
			else if (tmp->token == HERE_DOC && tmp->next->token == ALPHANUMERIC)
				tmp->next->token = LIMITOR;
		}
		tmp = tmp->next;
	}
}

void	get_token5(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	set_token_type(tmp);
	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp->token == ALPHANUMERIC)
			tmp->token = CMD;
		tmp = tmp->next;
	}
}
