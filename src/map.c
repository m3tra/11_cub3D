/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:22 by fporto            #+#    #+#             */
/*   Updated: 2023/06/18 05:47:38 by fporto           ###   ########.fr       */
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
		ft_free(new_map[y]);
	ft_free(new_map);
	return (res);
}

void	check_line(t_game *game, size_t y)
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
void	check_map(t_game *game)
{
	t_map	*map;
	int		player;
	size_t	y;
	size_t	x;
	char	c;

	player = 0;
	map = game->map;
	y = -1;
	// printf("max_heigth: %ld\n", map->max_height);
	while (++y < map->max_height)
	{
		// printf("line: %s\n", map->map_arr[y]);
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
		check_line(game, y);
	}
	if (!player)
		err_exit("Missing player @check_map", NULL);

	if (!is_map_closed(map))
		err_exit("Map not enclosed by walls", NULL);
}

// Advances file by n lines
void	skip_lines(int fd, size_t n)
{
	int		ret;
	char	*line;

	while (n > 0)
	{
		ret = get_next_line(fd, &line);
		if (!ret)
			break ;
		ft_free(line);
		n--;
	}
}

// Reads map file and sets it's max height and width in the struct
void	set_map_size(t_map *map, int fd)
{
	char	*line;
	int		ret;
	size_t	len;

	// skip_lines(fd, map->file_line_number_start);

	// Parse map part of input file
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret && line && line[0])
		{
			printf("line: %s\n", line);
			++map->max_height;
			len = ft_strlen(line);
			if (len > map->max_width)
				map->max_width = len;
			ft_free(line);
		}
		if (!ret)
			break ;
	}
}

// Allocates memory, zeros it, then pre-fills each tile with a space char
char	**prealloc_map_array(size_t max_height, size_t max_width)
{
	char	**map_arr;
	size_t	y;

	map_arr = ft_calloc(max_height + 1, sizeof(char *));
	if (!map_arr)
		err_exit("Failed ft_calloc @init_map", NULL);

	y = -1;
	while (++y < max_height)
	{
		map_arr[y] = ft_calloc(1, max_width + 1);
		if (!map_arr[y])
			err_exit("Failed ft_calloc @init_map", NULL);
		ft_memset(map_arr[y], ' ', max_width);
	}
	return (map_arr);
}

void	init_map(t_map *map, int fd)
{
	set_map_size(map, fd);
	if (map->max_height < 3 || map->max_width < 3)
		err_exit("Map size too small @init_map", NULL);

	map->map_arr = prealloc_map_array(map->max_height, map->max_width);
}
