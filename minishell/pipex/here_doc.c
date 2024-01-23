/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:16:31 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/06 13:32:14 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_2(t_data *data)
{
	data->here_status = 1;
	data->exit_code = 130;
}

t_here	*here_doc(t_data *data, char *str)
{
	int		i;
	int		stat;
	pid_t	pid;

	stat = 0;
	data->nb_here = count_hd(data->first);
	if (!data->nb_here)
		return (NULL);
	data->here = ft_calloc(sizeof(t_here), data->nb_here);
	ft_getdelims(str, data->here, data);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	i = -1;
	if (pid == 0)
		child_hd(data, str);
	else if (pid > 0)
		while (++i < data->nb_here)
			close(data->here[i].pipe[1]);
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		stat = WEXITSTATUS(stat);
	if (stat == 130)
		here_doc_2(data);
	return (NULL);
}

int	count_hd(t_list *list)
{
	int		nb;
	t_list	*tmp;

	nb = 0;
	tmp = list;
	while (tmp != NULL)
	{
		if (tmp->token == LIMITOR)
			nb++;
		tmp = tmp->next;
	}
	return (nb);
}

void	check_quotes(int *i, char *str)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
	}
	else if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"')
			(*i)++;
	}
}

void	ft_getdelims(char *str, t_here *here, t_data *data)
{
	int		nb;
	int		i;
	t_list	*tmp;

	i = -1;
	nb = 0;
	tmp = data->first;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			check_quotes(&i, str);
		else if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
			{
				while (tmp != NULL && tmp->token != LIMITOR)
					tmp = tmp->next;
				here[nb].delim = get_word(&str[++i], &tmp);
				pipe(here[nb++].pipe);
				if (tmp != NULL)
					tmp = tmp->next;
			}
		}
	}
}
