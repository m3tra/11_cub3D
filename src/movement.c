/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:24 by fporto            #+#    #+#             */
/*   Updated: 2023/06/18 08:12:01 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks if destination tile is valid and, if so, executes move
static void	can_move(t_game *game, t_float_p dest)
{
	t_int_p	tile;
	char	dest_tile;

	tile.x = dest.x / TILE_SIZE;
	tile.y = dest.y / TILE_SIZE;
	dest_tile = game->map->map_arr[tile.y][tile.x];
	if (dest_tile != WALL)
		game->player.pos = dest;
}

// Returns left or right destination tile on A or D keypress
static t_float_p	get_sideways_dest(t_entity player, int keycode)
{
	float		facing;
	t_float_p	delta;

	facing = player.facing;
	if (keycode == MLX_KEY_A)
	{
		facing += M_PI / 2;
		if (facing > 2 * M_PI)
			facing -= 2 * M_PI;
	}
	else if (keycode == MLX_KEY_D)
	{
		facing -= M_PI / 2;
		if (facing < 0)
			facing += 2 * M_PI;
	}
	delta.x = cos(facing) * STEP_DISTANCE;
	delta.y = -sin(facing) * STEP_DISTANCE;
	return (delta);
}

// Handle player movement on keypress
void	move(t_app *app, int keycode)
{
	t_entity	player;
	t_float_p	dest;

	player = app->game->player;
	dest = player.pos;
	if (keycode == MLX_KEY_W)
	{
		dest.x = player.pos.x + player.delta.x;
		dest.y = player.pos.y + player.delta.y;
	}
	else if (keycode == MLX_KEY_S)
	{
		dest.x = player.pos.x - player.delta.x;
		dest.y = player.pos.y - player.delta.y;
	}
	else if (keycode == MLX_KEY_A || \
			keycode == MLX_KEY_D)
	{
		dest = get_sideways_dest(player, keycode);
		dest.x = player.pos.x + dest.x;
		dest.y = player.pos.y + dest.y;
	}
	can_move(app->game, dest);
}

// Pivots player POV left/right
void	rotate_view(t_app *app, int keycode)
{
	float		*facing;
	t_float_p	*delta;

	facing = &app->game->player.facing;
	delta = &app->game->player.delta;
	if (keycode == MLX_KEY_LEFT)
	{
		*facing += 0.1;
		if (*facing > 2 * M_PI)
			*facing -= 2 * M_PI;
	}
	else if (keycode == MLX_KEY_RIGHT)
	{
		*facing -= 0.1;
		if (*facing < 0)
			*facing += 2 * M_PI;
	}
	delta->x = cos(*facing) * STEP_DISTANCE;
	delta->y = -sin(*facing) * STEP_DISTANCE;
}
