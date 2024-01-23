/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:40:57 by mpeulet           #+#    #+#             */
/*   Updated: 2022/11/16 19:32:27 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size && dest[i])
		i++;
	j = i + ft_strlen(src);
	dest += i;
	if (size != i)
	{
		while (*src)
		{
			if (size > i + 1)
			{
				*dest++ = *src;
				size--;
			}
			src++;
		}
		*dest = 0;
	}
	return (j);
}
