/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 08:08:47 by fheaton-          #+#    #+#             */
/*   Updated: 2023/06/18 10:23:36 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_surroundings(t_map *map, int row, int column)
{
	if (map->map_arr[row][column - 1] == ' '
		|| map->map_arr[row][column + 1] == ' '
		|| map->map_arr[row - 1][column] == ' '
		|| map->map_arr[row + 1][column] == ' ')
		return (0);
	else
		return (1);
}

int	is_map_closed(t_map *map)
{
	int		row;
	int		column;

	row = -1;
	while (++row < map->max_height)
	{
		column = -1;
		while (map->map_arr[row][++column] != '\0')
		{
			if (map->map_arr[row][column] == '0'
				|| map->map_arr[row][column] == 'N'
				|| map->map_arr[row][column] == 'S'
				|| map->map_arr[row][column] == 'E'
				|| map->map_arr[row][column] == 'W')
			{
				if (row == 0 || row == map->max_height -1
					|| column == 0 || column == map->max_width - 1)
					return (0);
				if (check_surroundings(map, row, column) == 0)
					return (0);
			}
		}
	}
	return (1);
}

void	check_line(t_game *game, int y)
{
	const char	*line;
	int			x;
	char		c;

	line = game->map->map_arr[y];
	check_invalid_chars(line);
	x = -1;
	while (++x < game->map->max_width)
	{
		c = line[x];
		if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			game->player = init_player(x, y, c);
	}
}

void	map_err_check(int player, t_game *game)
{
	if (!player)
		err_exit("Missing player @check_map", NULL);
	if (!is_map_closed(game->map))
		err_exit("Map not enclosed by walls", NULL);
}
