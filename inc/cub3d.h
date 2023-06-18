/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:47:57 by fporto            #+#    #+#             */
/*   Updated: 2023/06/18 08:38:06 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# include <unistd.h>
# include <errno.h>
# include <math.h>

# include "libft.h"
# include "color.h"

# include "mlx.h"
# include "mlx_keys.h"

# define TITLE			"cub3D"

# define BONUS			0

# include "map.h"
# include "defines.h"
# ifndef M_PI
#  define M_PI			3.141592653
# endif

# define FOV			1.570796

# define CIRCLE_RADIUS	20

# define STEP_DISTANCE	0.08

// Game

// Float x,y
typedef struct s_pos
{
	double		x;
	double		y;
}	t_float_p;

// Int x, y
typedef struct s_tile
{
	int			x;
	int			y;
}	t_int_p;

typedef struct s_check
{
	double			rx;
	double			ry;
	double			z;
	t_float_p		tex;
	int				**texture;
	double			lh;
	double			lo;
	double			texoff;
	t_float_p		off;
}	t_check;

/*
**	Facing directions (angle):
**		0 or 2 * M_PI	Right
**		M_PI / 2		Up
**		M_PI			Left
**		3 * M_PI / 2	Down
*/

typedef struct s_entity
{
	t_float_p	pos;
	float		facing;
	float		fix_f;
	t_float_p	delta;
}	t_entity;

typedef struct s_map
{
	const char	*filename;
	size_t		file_line_number_start;
	int			max_width;
	int			max_height;
	char		**map_arr;
}	t_map;

typedef struct s_tex
{
	char		*n_wall_path;
	char		*s_wall_path;
	char		*w_wall_path;
	char		*e_wall_path;
	int			**n_wall;
	int			**s_wall;
	int			**w_wall;
	int			**e_wall;
	u_int32_t	ceiling_color;
	u_int32_t	floor_color;
}	t_tex;

typedef struct s_game
{
	t_tex		*textures;
	t_map		*map;
	t_entity	player;
	size_t		n_torches;
	t_entity	*torches;
}	t_game;

// Screen

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_img;

typedef struct s_screen
{
	int			width;
	int			height;
	void		*win;
	t_img		*img;	
}	t_screen;

// App

typedef struct s_app
{
	void		*mlx;
	t_game		*game;
	t_screen	*screen;
	int			status_code;
}	t_app;

// Init
t_entity	init_player(int x, int y, char facing);
t_app		*init_app(const char *map_filename);

// Map
int			is_map_closed(t_map *map);
void		parse_line(t_game *game, int y);
void		set_map_size(t_map *map, int fd);
void		init_map(t_map *map, int fd);
void		skip_lines(int fd, size_t n);

// Map2
void		map_err_check(int player, t_game *game);
void		check_line(t_game *game, int y);
char		**map_dup(t_map *map);

// Img
t_img		*import_image(t_app *app, char a, int x, int y);
void		place_img(t_app *app, char tile, t_int_p p);

// Textures
void		load_textures(t_app *app);

// Parsing
void		parse_scene_description_file(t_app *app, const char *filename);

// Parsing2
void		parse_colors(t_tex *tex, const char *line);
u_int32_t	read_rgb(const char *line);
size_t		n_chars_before_whitespace(const char *line, size_t start_pos);
void		parse_map(t_map *map, int fd);
void		check_map_file_extension(const char *filename);

// Checks
void		check_invalid_chars(const char *line);
void		check_map(t_game *game);
void		check_macros(void);

// void		can_move(t_app *app, t_float_p dest);
void		move(t_app *app, int keycode);
void		rotate_view(t_app *app, int keycode);

// Colors
u_int32_t	create_trgb(u_int32_t t, u_int32_t r, u_int32_t g, u_int32_t b);
u_int32_t	get_t(u_int32_t trgb);
u_int32_t	get_r(u_int32_t trgb);
u_int32_t	get_g(u_int32_t trgb);
u_int32_t	get_b(u_int32_t trgb);

// 2D
void		draw_2d_background(t_app *app);
void		draw2d(t_app *app);

// 2D Drawing
void		draw_circle2(t_img *img, int x, int y, u_int32_t color);
void		draw_circle(t_img *img, t_int_p pixel, u_int32_t color);

// 3D
t_check		*check_wall(t_game *g, t_float_p pos, double ang, float pa);
void		draw_3d_background(t_app *app, u_int32_t f_clr, u_int32_t c_clr);
int			draw3d(t_app *app);

// Cleanup
void		free_matrix(void **matrix);
void		free_app(t_app *app);

// Utils
void		err_exit(const char *err, t_app *app);
int			stop(void *param);
void		setup_mlx_hooks(t_app *app);

// MLX Utils
void		my_mlx_pixel_put(t_img *img, int x, int y, u_int32_t color);
void		my_mlx_pixel_put2(t_img *img, int x, int y, int color);
char		*my_mlx_get_data_addr(t_img *img);
t_img		*my_mlx_new_image(void *mlx, int width, int height);
void		my_mlx_put_image_to_window(t_app *app);

#endif
