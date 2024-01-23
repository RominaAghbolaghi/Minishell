/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 06:05:17 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:32:03 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len_word(char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || ft_strchr("\'\"",
				str[i])))
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && !ft_strchr("\'\"",
			str[i]))
	{
		i++;
		r++;
	}
	return (r);
}

int	get_word2(char *str, char **new, int *i, int *r)
{
	int	j;

	j = 0;
	if (str[*i] == '$')
	{
		if ((str[(*i) + 1] && str[*i + 1] != '\'' && str[(*i) + 1] != '\"')
			|| str[(*i) + 1] == '\0')
		{
			j = 1;
			(*new)[(*r)++] = '$';
			(*i) = (*i) + 1;
		}
		else if (str[(*i) + 1] && (str[(*i) + 1] == '\''
				|| str[(*i) + 1] == '\"'))
			(*i) = (*i) + 1;
	}
	else if (str[(*i)] && str[(*i)] != '\'' && str[(*i)] != '\"')
		(*new)[(*r)++] = str[(*i)++];
	else
		(*i) = (*i) + 1;
	return (j);
}

void	get_word1(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] < 0)
			(*str)[i] = (*str)[i] * (-1);
		i++;
	}
}

void	get_word3(t_list **tmp, char *new)
{
	free((*tmp)->content);
	(*tmp)->content = ft_strdup(new);
}

char	*get_word(char *str, t_list **tmp)
{
	int		i;
	int		r;
	int		j;
	char	*new;

	get_word1(&str);
	new = malloc(get_len_word(str) + 1);
	if (!new)
		return (NULL);
	i = 0;
	r = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || ft_strchr("\'\"",
				str[i])))
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && !ft_strchr("\'\"",
			str[i]))
	{
		if (get_word2(str, &new, &i, &r) == 1)
			j = 1;
	}
	new[r] = 0;
	if (j == 1)
		get_word3(tmp, new);
	return (new);
}
