/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 08:15:31 by fheaton-          #+#    #+#             */
/*   Updated: 2023/06/18 08:16:56 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Prints error message and exits d program if mapfile name doesn't end in .cub
void	check_map_file_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len > 256)
		err_exit("Map file name is too long", NULL);
	if (!ft_strstr(filename, ".cub"))
		err_exit("Map file required to be in .cub format", NULL);
}

// Reads map from file into memory
void	parse_map(t_map *map, int fd)
{
	char	*line;
	int		y;

	skip_lines(fd, map->file_line_number_start + 1);
	y = -1;
	while (++y < map->max_height)
	{
		get_next_line(fd, &line);
		if (line && line[0])
		{
			ft_memcpy(map->map_arr[y], line, ft_strlen(line));
			ft_free(line);
		}
	}
}

size_t	n_chars_before_whitespace(const char *line, size_t start_pos)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = start_pos;
	while (line && line[i] && !ft_isspace(line[i]))
	{
		n++;
		i++;
	}
	return (n);
}

u_int32_t	read_rgb(const char *line)
{
	size_t		i;
	u_int32_t	r;
	u_int32_t	g;
	u_int32_t	b;

	r = 0;
	g = 0;
	b = 0;
	if (!line)
		err_exit("Missing line @read_rgb", NULL);
	i = 1;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i] && line[i] != ',' && ft_isdigit(line[i]))
		r = r * 10 + (line[i++] - 48);
	i++;
	while (line[i] && line[i] != ',' && ft_isdigit(line[i]))
		g = g * 10 + (line[i++] - 48);
	i++;
	while (line[i] && line[i] != ',' && ft_isdigit(line[i]))
		b = b * 10 + (line[i++] - 48);
	if (r > 255 || g > 255 || b > 255)
		err_exit("Bad rgb value @read_rgb", NULL);
	return (create_trgb(255, r, g, b));
}

void	parse_colors(t_tex *tex, const char *line)
{
	if (!line)
		err_exit("Missing line @parse_colors", NULL);
	if (line[0] == 'F')
		tex->floor_color = read_rgb(line);
	else if (line[0] == 'C')
		tex->ceiling_color = read_rgb(line);
}
