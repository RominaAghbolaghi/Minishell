/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:45:56 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:30:28 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_quote(char *line, t_data *data)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (quote == 0 && line[i] == '\'')
				quote = 2;
			else if (quote == 0 && line[i] == '\"')
				quote = 1;
			else if (quote == 2 && line[i] == '\'')
				quote = 0;
			else if (quote == 1 && line[i] == '\"')
				quote = 0;
		}
	}
	if (quote != 0)
	{
		data->exit_code = 2;
		return (ft_printf_fd(2, "minishell: syntax error quote unclosed\n"), 2);
	}
	return (0);
}

void	ft_negative(char *line)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (quote == 0 && line[i] == '\'')
				quote = 2;
			else if (quote == 0 && line[i] == '\"')
					quote = 1;
			while (line[++i] && ((line[i] != 34 && quote == 1)
					|| (line[i] != 39 && quote == 2)))
				line[i] = line[i] * -1;
			quote = 0;
		}
	}
}

void	ft_positive(t_data *data)
{
	t_list	*tmp;
	int		i;

	tmp = data->first;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->next != NULL
			&& (tmp->token == SIMPLE_QUOTE || tmp->token == DOUBLE_QUOTE))
		{
			if (tmp->next->token == ALPHANUMERIC)
			{
				tmp = tmp->next;
				while (tmp->content[i])
				{
					if (tmp->content[i] < 0)
						tmp->content[i] = tmp->content[i] * -1;
					i++;
				}
			}
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
}

void	replace_quote(t_data *data)
{
	t_list	*tmp;
	int		i;

	tmp = data->first;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp && tmp->token == SIMPLE_QUOTE)
			tmp = replace_single_quotes(tmp, &i);
		if (tmp && tmp->token == DOUBLE_QUOTE)
			tmp = replace_double_quotes(tmp, &i);
		if (tmp != NULL && i == 0)
			tmp = tmp->next;
	}
}

void	replace_dollar_quote(t_list *lst)
{
	int		i;

	i = 0;
	while (lst->content[i])
	{
		if (lst->content[i] == '$' && (ft_isalnum(lst->content[i + 1]) == 1
				|| lst->content[i + 1] == '_' || lst->content[i + 1] == '?'))
		{
			if (ft_isalpha(lst->content[i + 1]) == 1
				|| lst->content[i + 1] == '_')
				lst->content = replace_dollar_alpha(lst);
			else if (lst->content[i + 1] == '?')
				lst->content = replace_dollar_return_code(lst);
			else if (ft_isdigit(lst->content[i + 1]) == 1)
				lst->content = replace_dollar_digit(lst);
			i = 0;
		}
		else
			i++;
	}
}
