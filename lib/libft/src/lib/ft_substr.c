/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 19:08:35 by fporto            #+#    #+#             */
/*   Updated: 2022/11/25 17:15:18 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	rng(const char *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	if (!s[i] || start > ft_strlen(s))
		return (0);
	while (s[start + i] && i < len)
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	range;

	if (!s)
		return (NULL);
	j = 0;
	range = rng(s, start, len);
	str = malloc(range + 1);
	if (ft_strlen(s) >= start)
	{
		if (!str)
			return (NULL);
		i = start;
		while (s[i] && j < range)
		{
			str[j] = s[i];
			i++;
			j++;
		}
	}
	str[j] = '\0';
	return (str);
}
