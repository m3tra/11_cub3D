/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:04 by fporto            #+#    #+#             */
/*   Updated: 2023/06/18 07:58:34 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_invalid_chars(const char *line)
{
	const char	*chars;
	size_t		x;
	int			bad;
	size_t		i;

	chars = MAP_CHARS;
	x = -1;
	while (line[++x])
	{
		bad = 1;
		i = -1;
		while (chars[++i])
			if (line[x] == chars[i])
				bad = 0;
		if (bad)
			err_exit("Bad tile in map @check_invalid_chars", NULL);
	}
}

void	check_macros(void)
{
	if (DIMENTIONS != 2 && DIMENTIONS != 3)
		err_exit("DIMENTIONS not 2 or 3", NULL);
}
