/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:31:31 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/06 13:55:51 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen2(char const *s)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_bis(char const *s1, char const *s2)
{
	char	*str;
	int		j;
	int		i;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!s1 && !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen2(s1) + ft_strlen2(s2) + 1));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
		str[k++] = s1[i++];
	while (s2 && s2[j])
		str[k++] = s2[j++];
	str[k] = '\0';
	return (free((char *)s1), free((char *)s2), str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		j;
	int		i;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!s1 && !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen2(s1) + ft_strlen2(s2) + 1));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
		str[k++] = s1[i++];
	while (s2 && s2[j])
		str[k++] = s2[j++];
	str[k] = '\0';
	return (str);
}

int	ft_strlen33(char const *s)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*str;
	int		j;
	int		i;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	str = malloc(sizeof(char) * (ft_strlen33(s1) + ft_strlen33(s2) + 1));
	if (!str)
		return (NULL);
	if (s1)
		while (s1[i])
			str[k++] = s1[i++];
	while (s2[j])
		str[k++] = s2[j++];
	str[k] = '\0';
	return (str);
}
