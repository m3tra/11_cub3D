/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 03:32:33 by fporto            #+#    #+#             */
/*   Updated: 2023/06/18 07:47:03 by fheaton-         ###   ########.fr       */
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
static void	free_textures(t_tex *textures)
{
	if (textures)
	{
		if (textures->n_wall)
			free_matrix((void **)textures->n_wall);
		if (textures->s_wall)
			free_matrix((void **)textures->s_wall);
		if (textures->e_wall)
			free_matrix((void **)textures->e_wall);
		if (textures->w_wall)
			free_matrix((void **)textures->w_wall);
		ft_free(textures->n_wall_path);
		ft_free(textures->s_wall_path);
		ft_free(textures->e_wall_path);
		ft_free(textures->w_wall_path);
		free(textures);
	}
}

// Frees map object
static void	free_map(t_map *map)
{
	int	y;

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
		if (game->textures)
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
