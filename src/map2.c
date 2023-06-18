/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 08:08:47 by fheaton-          #+#    #+#             */
/*   Updated: 2023/06/18 08:33:47 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	recursive_map_check(t_map *map, char **map_arr, int x, int y)
{
	char	c;

	c = map_arr[y][x];
	if (((!y || y == map->max_height - 1 || \
		!x || x == map->max_width - 1) && \
		c != '1' && c != ' ') || \
		c == ' ')
		return (0);
	if (c == '1' || c == 'X')
		return (1);
	if (map_arr[y - 1][x] == ' ' || \
		map_arr[y + 1][x] == ' ' || \
		map_arr[y][x - 1] == ' ' || \
		map_arr[y][x + 1] == ' ')
		return (0);
	map_arr[y][x] = 'X';
	return (recursive_map_check(map, map_arr, x, y - 1) && \
			recursive_map_check(map, map_arr, x, y + 1) && \
			recursive_map_check(map, map_arr, x - 1, y) && \
			recursive_map_check(map, map_arr, x + 1, y));
}

char	**map_dup(t_map *map)
{
	char	**map_arr;
	char	**new_map;
	int		y;

	map_arr = map->map_arr;
	new_map = ft_calloc(map->max_height + 1, sizeof(char *));
	if (!new_map)
		err_exit("Failed ft_calloc @map_dup", NULL);
	y = -1;
	while (++y < map->max_height)
		new_map[y] = ft_strdup(map_arr[y]);
	return (new_map);
}

int	is_map_closed(t_map *map)
{
	int		res;
	char	**new_map;
	int		y;
	int		x;

	res = 0;
	new_map = map_dup(map);
	y = -1;
	while (++y < map->max_height)
	{
		x = -1;
		while (++x < map->max_width)
			if (map->map_arr[y][x] == '0')
				res = recursive_map_check(map, new_map, x, y);
	}
	y = -1;
	while (++y < map->max_height)
		free(new_map[y]);
	free(new_map);
	return (res);
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
