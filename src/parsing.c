/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 02:18:08 by fporto            #+#    #+#             */
/*   Updated: 2023/06/18 06:02:02 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

// Reads map from file into memory
void	parse_map(t_map *map, int fd)
{
	int		ret;
	char	*line;
	size_t	y;

	skip_lines(fd, map->file_line_number_start + 1);

	y = -1;
	while (++y < map->max_height)
	{
		ret = get_next_line(fd, &line);
		printf("line2: %s\n", line);
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
	size_t	i;
	u_int32_t	r;
	u_int32_t	g;
	u_int32_t	b;

	r = 0;
	g = 0;
	b = 0;

	if (!line)
		err_exit("Missing line @read_rgb", NULL);

	// skip whitespace
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

	if (line[0] == 'F') // Floor color
		tex->floor_color = read_rgb(line);
	else if (line[0] == 'C') // Ceiling color
		tex->ceiling_color = read_rgb(line);
}

char	*read_file_path(const char *line)
{
	char	*path;

	if (!line)
		err_exit("Missing line @read_file_path", NULL);

	// skip whitespace before path
	size_t	skips;

	skips = n_chars_before_whitespace(line, 0);
	while (skips--)
		line++;

	while (*line && ft_isspace(*line))
		line++;

	path = ft_strdup(line);

	// remove possible whitespace at the end
	size_t	last_char;

	last_char = ft_strlen(line) - 1;

	while (ft_isspace(line[last_char]))
		path[last_char--] = '\0';

	if (!path)
		err_exit("Error reading path @read_file_path", NULL);
	return (path);
}

void	print_texture_paths(t_tex *tex)
{
	printf("n_wall_path: |%s|\n", tex->n_wall_path);
	printf("s_wall_path: |%s|\n", tex->s_wall_path);
	printf("w_wall_path: |%s|\n", tex->w_wall_path);
	printf("e_wall_path: |%s|\n", tex->e_wall_path);
	printf("floor color: %u\n", tex->floor_color);
	printf("ceiling color: %u\n", tex->ceiling_color);
}

void	parse_texture_path(t_game *game, const char *line)
{
	t_tex	*tex;

	if (!line)
		err_exit("Missing line @parse_texture_path", NULL);

	tex = game->textures;

	if (line[0] == 'N' && line[1] == 'O' && !tex->n_wall_path)
		tex->n_wall_path = read_file_path(line);
	else if (line[0] == 'S' && line[1] == 'O' && !tex->s_wall_path)
		tex->s_wall_path = read_file_path(line);
	else if (line[0] == 'W' && line[1] == 'E' && !tex->w_wall_path)
		tex->w_wall_path = read_file_path(line);
	else if (line[0] == 'E' && line[1] == 'A' && !tex->e_wall_path)
		tex->e_wall_path = read_file_path(line);
	else
	{
		printf("Bad line: |%s|\n", line);
		err_exit("Failed texture parsing @parse_textures_path", NULL);
	}
}

// Returns how many lines were read before getting to map section
size_t	parse_tex_and_colors(t_game *game, int fd)
{
	size_t	n_lines_read;
	char	*line;
	int		ret;
	t_tex	*tex;

	tex = game->textures;

	n_lines_read = 0;
	while (1)
	{
		// printf("test\n");
		ret = get_next_line(fd, &line);
		if (line && line[0])
		{
			if (n_chars_before_whitespace(line, 0) == 2)
				parse_texture_path(game, line);
			else if (n_chars_before_whitespace(line, 0) == 1)
				parse_colors(tex, line);
		}
		ft_free(line);
		n_lines_read++;
		if ((tex->n_wall_path && tex->s_wall_path && \
			tex->w_wall_path && tex->e_wall_path && \
			tex->ceiling_color && tex->floor_color) || \
			!ret
		)
			break ;
	}
	return (n_lines_read);
}

void	parse_scene_description_file(t_app *app, const char *filename)
{
	t_game	*game;
	int		fd;

	if (!filename)
		err_exit("Missing filename @parse_scene_description_file", NULL);


	game = app->game;

	// game->map->filename = filename;
	check_map_file_extension(filename);


	fd = open(filename, O_RDONLY);
	if (fd == -1)
		err_exit("Invalid file path @parse_description_file", NULL);

	game->textures = ft_calloc(1, sizeof(t_tex));
	if (!game->textures)
		err_exit("Failed ft_calloc @parse_scene_description_file", app);

	game->map->file_line_number_start = parse_tex_and_colors(app->game, fd);
	// print_texture_paths(game->textures);
	load_textures(app);

	init_map(game->map, fd);
	close(fd);


	fd = open(filename, O_RDONLY);
	if (fd == -1)
		err_exit("Invalid file path @parse_description_file", NULL);

	parse_map(game->map, fd);
	check_map(game);

	close(fd);
}
