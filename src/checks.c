/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:04 by fporto            #+#    #+#             */
/*   Updated: 2023/03/14 20:30:31 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks if map file's given line has invalid chars
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

// Prints error message and exits the program if map file name doens't end in .cub
void	check_map_file_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len > 256)
		err_exit("Map file name is too long", NULL);
	if (!ft_strstr(filename, ".cub"))
		err_exit("Map file required to be in .cub format", NULL);
}

// Checks if header defines are valid
void	check_macros(void)
{
	if (DIMENTIONS != 2 && DIMENTIONS != 3)
		err_exit("DIMENTIONS not 2 or 3", NULL);
	if (TILE_SIZE < 8)
		err_exit("TILE_SIZE too small", NULL);
}
