/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:08 by fporto            #+#    #+#             */
/*   Updated: 2023/06/18 08:01:30 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns allocated and initialized t_screen*
static void	init_screen(t_app *app)
{
	t_screen	*s;

	s = app->screen;
	if (DIMENTIONS == 2)
	{
		s->width = app->game->map->max_width * TILE_SIZE;
		s->height = app->game->map->max_height * TILE_SIZE;
	}
	else if (DIMENTIONS == 3)
	{
		s->width = WIN_WIDTH;
		s->height = WIN_HEIGHT;
	}
	s->win = mlx_new_window(app->mlx, s->width, s->height, TITLE);
	if (!s->win)
		err_exit("Failed mlx_new_window @init_screen", app);
	s->img = my_mlx_new_image(app->mlx, s->width, s->height);
}

// Sets player's position to middle of given tile and other default values
t_entity	init_player(int x, int y, char facing)
{
	t_entity	player;

	player.pos.x = (x * TILE_SIZE) + 0.5;
	player.pos.y = (y * TILE_SIZE) + 0.5;
	if (facing == 'N')
		player.facing = M_PI / 2;
	else if (facing == 'S')
		player.facing = 3 * M_PI / 2;
	else if (facing == 'W')
		player.facing = M_PI;
	else
		player.facing = 0;
	player.delta.x = cos(player.facing) * STEP_DISTANCE;
	player.delta.y = -sin(player.facing) * STEP_DISTANCE;
	return (player);
}

// Returns allocated and initialized t_app*
t_app	*init_app(const char *scene_description_filename)
{
	t_app	*app;

	app = ft_calloc(1, sizeof(t_app));
	if (!app)
		err_exit("Failed ft_calloc @init_app", app);
	app->mlx = mlx_init();
	if (!app->mlx)
		err_exit("Failed mlx_init @init_app", app);
	app->game = ft_calloc(1, sizeof(t_game));
	if (!app->game)
		err_exit("Failed ft_calloc @init_game", NULL);
	app->game->map = ft_calloc(1, sizeof(t_map));
	if (!app->game->map)
		err_exit("Failed ft_calloc @init_map", NULL);
	app->screen = ft_calloc(1, sizeof(t_screen));
	if (!app->screen)
		err_exit("Failed ft_calloc @init_screen", app);
	parse_scene_description_file(app, scene_description_filename);
	init_screen(app);
	return (app);
}
