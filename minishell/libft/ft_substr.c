/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:11:25 by mpeulet           #+#    #+#             */
/*   Updated: 2023/12/06 13:56:27 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlen3(char const *s)
{
	unsigned int	k;

	k = 0;
	while (s[k])
		k++;
	return (k);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (start > ft_strlen3(s))
		return (ft_strdup(""));
	if (len > (ft_strlen3(s) - start))
		len = ft_strlen3(s) - start;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (i < start && s[i])
		i++;
	while (j < len && s[i])
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}
