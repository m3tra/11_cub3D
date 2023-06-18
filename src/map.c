/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:22 by fporto            #+#    #+#             */
/*   Updated: 2023/06/18 08:18:14 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map(t_game *game)
{
	int		player;
	int		y;
	int		x;
	char	c;

	player = 0;
	y = -1;
	while (++y < game->map->max_height)
	{
		x = -1;
		while (++x < game->map->max_width)
		{
			c = game->map->map_arr[y][x];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				if (player)
					err_exit("Only one player allowed", NULL);
				player = 1;
			}
		}
		check_line(game, y);
	}
	map_err_check(player, game);
}

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

void	set_map_size(t_map *map, int fd)
{
	char	*line;
	int		ret;
	int		len;

	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret && line && line[0])
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
}

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
