/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:22 by fporto            #+#    #+#             */
/*   Updated: 2023/03/15 19:14:24 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// WIP
int	recursive_map_check(t_map *map, char **map_arr, size_t x, size_t y)
{
	char	c;

	c = map_arr[y][x];

	// If c is at the border of the map and isn't '1' or ' ' colapse branch (0)
	if (((!y || y == map->max_height - 1 || \
		!x || x == map->max_width - 1) && \
		c != '1' && c != ' ') || \
		c == ' ')
		return (0);

	// If c is a wall or was already checked ('X') return 1
	if (c == '1' || c == 'X')
		return (1);

	// Check current tile's four adjacent ones for ' '
	if (map_arr[y - 1][x] == ' ' || \
		map_arr[y + 1][x] == ' ' || \
		map_arr[y][x - 1] == ' ' || \
		map_arr[y][x + 1] == ' ')
		return (0);


	// Tag current tile as already checked
	map_arr[y][x] = 'X';

	// Branch out to 4 adjacent tiles
	return (recursive_map_check(map, map_arr, x, y - 1) && \
			recursive_map_check(map, map_arr, x, y + 1) && \
			recursive_map_check(map, map_arr, x - 1, y) && \
			recursive_map_check(map, map_arr, x + 1, y));
}

// Allocates map array clone and returns it
char	**map_dup(t_map *map)
{
	char	**map_arr;
	char	**new_map;
	size_t	y;

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
	size_t	y;
	size_t	x;

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

void	parse_line(t_game *game, size_t y)
{
	const char	*line;
	size_t		x;
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

// Checks if map is valid
void	parse_map(t_game *game)
{
	t_map	*map;
	int		player;
	size_t	y;
	size_t	x;
	char	c;

	player = 0;
	map = game->map;
	y = -1;
	while (++y < map->max_height)
	{
		x = -1;
		while (++x < map->max_width)
		{
			c = map->map_arr[y][x];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				if (player)
					err_exit("Only one player allowed", NULL);
				player = 1;
			}
			else if (c == 'T')
				++game->n_torches;
		}
		parse_line(game, y);
	}
	if (!player)
		err_exit("Missing player @parse_map", NULL);
}

// Reads map file and sets it's max height and width in the struct
void	set_map_size(t_map *map)
{
	int		fd;
	char	*line;
	int		ret;
	size_t	len;

	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		err_exit("Invalid file path @set_map_size", NULL);

	while (1)
	{
		ret = get_next_line(fd, &line);
		if (line && line[0])
		{
			++map->max_height;
			len = ft_strlen(line);
			if (len > map->max_width)
				map->max_width = len;
		}
		ft_free(line);
		if (!ret)
			break ;
	}
	close(fd);
}

// Reads map from file into memory
void	load_map(t_map *map)
{
	int		fd;
	int		ret;
	char	*line;
	size_t	y;

	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		err_exit("Invalid file path @load_map", NULL);

	y = -1;
	while (++y < map->max_height)
	{
		ret = get_next_line(fd, &line);
		if (line && line[0])
		{
			ft_memcpy(map->map_arr[y], line, ft_strlen(line));
			ft_free(line);
		}
	}
	close(fd);
}

t_map	*init_map(const char *filename)
{
	t_map	*map;
	size_t	y;

	check_map_file_extension(filename);

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		err_exit("Failed ft_calloc @init_map", NULL);
	map->filename = filename;

	set_map_size(map);
	if (map->max_height < 3 || map->max_width < 3)
		err_exit("Map size too small @init_map", NULL);

	map->map_arr = ft_calloc(map->max_height + 1, sizeof(char *));
	if (!map->map_arr)
		err_exit("Failed ft_calloc @init_map", NULL);

	y = -1;
	while (++y < map->max_height)
	{
		map->map_arr[y] = ft_calloc(1, map->max_width + 1);
		if (!map->map_arr[y])
			err_exit("Failed ft_calloc @init_map", NULL);
		ft_memset(map->map_arr[y], ' ', map->max_width);
	}

	load_map(map);

	return (map);
}
