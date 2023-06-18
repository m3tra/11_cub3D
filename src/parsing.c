/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 02:18:08 by fporto            #+#    #+#             */
/*   Updated: 2023/06/18 10:32:29 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*read_file_path(const char *line)
{
	char	*path;
	size_t	skips;
	size_t	last_char;

	if (!line)
		err_exit("Missing line @read_file_path", NULL);
	skips = n_chars_before_whitespace(line, 0);
	while (skips--)
		line++;
	while (*line && ft_isspace(*line))
		line++;
	path = ft_strdup(line);
	last_char = ft_strlen(line) - 1;
	while (ft_isspace(line[last_char]))
		path[last_char--] = '\0';
	if (!path)
		err_exit("Error reading path @read_file_path", NULL);
	return (path);
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
	t_tex	*tex;

	tex = game->textures;
	n_lines_read = 0;
	while (get_next_line(fd, &line))
	{
		if (line && line[0])
		{
			if (n_chars_before_whitespace(line, 0) == 2)
				parse_texture_path(game, line);
			else if (n_chars_before_whitespace(line, 0) == 1)
				parse_colors(tex, line);
		}
		ft_free(line);
		n_lines_read++;
		if ((tex->n_wall_path && tex->s_wall_path && tex->w_wall_path && \
			tex->e_wall_path && tex->ceiling_color && tex->floor_color))
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
	check_map_file_extension(filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		err_exit("Invalid file path @parse_description_file", NULL);
	game->textures = ft_calloc(1, sizeof(t_tex));
	if (!game->textures)
		err_exit("Failed ft_calloc @parse_scene_description_file", app);
	game->map->file_line_number_start = parse_tex_and_colors(app->game, fd);
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
