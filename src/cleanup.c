/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 03:32:33 by fporto            #+#    #+#             */
/*   Updated: 2023/03/15 16:05:20 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Frees screen object
static void	free_screen(t_app *app)
{
	t_screen	*screen;

	screen = app->screen;
	if (app->mlx && screen)
	{
		if (screen->img && screen->img->img)
			mlx_destroy_image(app->mlx, screen->img->img);
		ft_free(screen->img);
		if (screen->win)
			mlx_destroy_window(app->mlx, screen->win);
		free(screen);
	}
}

// Frees textures object
static void	free_textures(t_textures *textures)
{
	if (textures)
	{
		ft_free(textures->n_wall);
		ft_free(textures->s_wall);
		ft_free(textures->w_wall);
		ft_free(textures->e_wall);
		free(textures);
	}
}

// Frees map object
static void	free_map(t_map *map)
{
	size_t	y;

	if (map)
	{
		y = -1;
		while (++y < map->max_height)
			ft_free(map->map_arr[y]);
		ft_free(map->map_arr);
		free(map);
	}
}

// Frees game object
static void	free_game(t_game *game)
{
	if (game)
	{
		free_textures(game->textures);
		free_map(game->map);
		free(game);
	}
}

// Frees app object
void	free_app(t_app *app)
{
	if (app)
	{
		free_game(app->game);
		free_screen(app);
		free(app);
	}
}
