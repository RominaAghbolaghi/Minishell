/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:54:14 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/07 14:24:47 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atoull_exit(char *str, int e)
{
	int					i;
	int					sign;
	unsigned long long	nb;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == 43 || str[i] == 45)
		if (str[i++] == 45)
			sign *= -1;
	while (ft_isdigit(str[i]))
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
		if (nb > LL_MAXOU || (nb > (LL_MAXOU + 1) && sign == -1))
		{
			if (e == 1)
				return (free(str), ft_printf_fd(2, EXIT_ERR, str), 2);
			else
				return (free(str), 2);
		}
	}
	return (free (str), (long long)nb * sign);
}

int	ft_is_sign(char c)
{
	if (c == '-' || c == '+')
		return (1);
	else
		return (0);
}

int	exit_error(char **cmd, t_data *data, int e)
{
	if (cmd[2])
	{
		if (e == 1)
		{
			ft_printf_fd(2, EXIT_NBR, cmd[1]);
			free_data_2_and_exit(data, 1);
		}
		return (1);
	}
	return (0);
}

int	exit_builtin(char **cmd, t_data *data, int e)
{
	long long	i;
	char		*cmd1;

	(void)data;
	if (e == 1)
		printf("exit\n");
	if (!cmd[1])
		free_data_2_and_exit(data, 0);
	i = -1;
	while (cmd[1][++i])
	{
		if (!ft_is_sign(cmd[1][i]) && !ft_isdigit(cmd[1][i]))
		{
			if (e == 1)
				ft_printf_fd(2, EXIT_ERR, cmd[1]);
			free_data_2_and_exit(data, 2);
		}
	}
	if (exit_error(cmd, data, e))
		return (1);
	cmd1 = ft_strdup(cmd[1]);
	free_data_2_and_exit(data, ft_atoull_exit(cmd1, e));
	return (0);
}
