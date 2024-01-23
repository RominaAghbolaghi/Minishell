/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:51:44 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/06 13:23:18 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_echo_option(char **echo, int *i, int *n)
{
	int	j;

	if (*i == 1)
	{
		while (echo[*i] && echo[*i][0] == 45 && echo[*i][1] == 'n')
		{
			while (echo[*i] && echo[*i][0] == 45 && echo[*i][1] == 'n')
			{
				j = 1;
				while (echo[*i][j])
				{
					if (echo[*i][j] != 'n')
						return ;
					j++;
				}
				(*i)++;
			}
			*n = 1;
		}
	}
}

void	echo(char **echo)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (echo[i])
	{
		parse_echo_option(echo, &i, &j);
		if (!echo[i])
			break ;
		ft_putstr_fd(echo[i], 1);
		if (echo[i + 1])
			ft_putchar_fd(32, 1);
		i++;
	}
	if (j == 0)
		ft_putchar_fd(10, 1);
}
