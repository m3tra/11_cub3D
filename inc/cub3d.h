/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:47:57 by fporto            #+#    #+#             */
/*   Updated: 2023/06/01 10:11:35 by fheaton-         ###   ########.fr       */
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

# define BONUS			1

# include "map.h"
# ifndef M_PI
#  define M_PI			3.141592653
# endif

# define DIMENTIONS		2
# define WIN_WIDTH		1280
# define WIN_HEIGHT		720

# define CIRCLE_RADIUS	75

# define STEP_DISTANCE	5

// Game

// Float x,y
typedef struct s_pos
{
	float		x;
	float		y;
}	t_float_p;

// Int x, y
typedef struct s_tile
{
	int			x;
	int			y;
}	t_int_p;

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
	t_float_p	delta;
}	t_entity;

typedef struct s_map
{
	const char	*filename;
	size_t		max_width;
	size_t		max_height;
	char		**map_arr;
}	t_map;

typedef struct s_textures
{
	char		*n_wall;
	char		*s_wall;
	char		*w_wall;
	char		*e_wall;
	u_int32_t	ceiling_color;
	u_int32_t	floor_color;
}	t_textures;

typedef struct s_game
{
	t_textures	*textures;
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
	size_t		width;
	size_t		height;
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
void		parse_line(t_game *game, size_t y);
void		set_map_size(t_map *map);
void		load_map(t_map *map);
t_map		*init_map(const char *filename);

// Img

t_img		*import_image(t_app *app, char a, int x, int y);
void		place_img(t_app *app, char tile, t_int_p p);

// Checks

void		check_invalid_chars(const char *line);
void		parse_map(t_game *game);
void		check_map_file_extension(const char *filename);
void		check_macros(void);

// Movement

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
int			draw2d(t_app *app);

// 2D Drawing

void		draw_circle(t_img *img, t_int_p pixel, u_int32_t color);

// 3D

void		draw_3d_background(t_app *app);
int			draw3d(t_app *app);

// Cleanup

void		free_app(t_app *app);

// Utils

void		err_exit(const char *err, t_app *app);
int			stop(void *param);
void		setup_mlx_hooks(t_app *app);

// MLX Utils

void		my_mlx_pixel_put(t_img *img, int x, int y, u_int32_t color);
char		*my_mlx_get_data_addr(t_img *img);
t_img		*my_mlx_new_image(void *mlx, int width, int height);
void		my_mlx_put_image_to_window(t_app *app);

#endif
