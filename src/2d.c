/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:30:46 by fporto            #+#    #+#             */
/*   Updated: 2023/06/07 17:15:14 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define M_P2	(M_PI/2)
#define M_P3	(3*M_PI/2)
#define DR		0.01745329

// Paints entire screen as gray
void	draw_2d_background(t_app *app)
{
	t_screen	*screen;
	size_t		x;
	size_t		y;

	screen = app->screen;
	y = -1;
	while (++y < screen->height)
	{
		x = -1;
		while (++x < screen->width)
			my_mlx_pixel_put(screen->img, x, y, create_trgb(255, 85, 85, 85));
	}
}

// Draws square tile at given pixel position
void	draw_tile(t_app *app, t_int_p pixel, u_int32_t trgb)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (++y < TILE_SIZE - 1)
	{
		x = 0;
		while (++x < TILE_SIZE - 1)
			my_mlx_pixel_put(app->screen->img, x + pixel.x, y + pixel.y, trgb);
	}
}

// Returns given tile's color
u_int32_t	pick_color(char map_tile)
{
	u_int32_t	color;

	if (map_tile == WALL)
		color = create_trgb(255, 0, 0, 0);			// Wall			(black)
	else if (map_tile == DOOR)
		color = create_trgb(255, 255, 0, 255);		// Door			(purple)
	else if (map_tile == TORCH)
		color = create_trgb(255, 255, 255, 0);		// Enemy		(red)
	else
		color = create_trgb(255, 255, 255, 255);	// Empty tile	(white)
	return (color);
}

void	draw_map(t_app *app)
{
	t_map		*map;
	size_t		tile_y;
	size_t		tile_x;
	t_int_p		pixel;
	u_int32_t	color;

	map = app->game->map;
	tile_y = -1;
	while (++tile_y < map->max_height)
	{
		tile_x = -1;
		while (++tile_x < map->max_width)
		{
			color = pick_color(map->map_arr[tile_y][tile_x]);
			pixel.x = tile_x * TILE_SIZE;
			pixel.y = tile_y * TILE_SIZE;
			draw_tile(app, pixel, color);
		}
	}
}

float dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}

void draw_rays(t_app *app, t_float_p pos, float pa)
{
	t_map		*map;
	u_int32_t	color;
	double		dx, dy;
	size_t 		dof;
	float 		ra, rx, ry;
	float		yo, xo, disT;
	size_t		mx, my;

	color = create_trgb(255, 255, 0, 0);
	map = app->game->map;
	ra = pa + DR*30;
	if (ra < 0)
		ra += 2*M_PI;
	if (ra > 2*M_PI)
		ra -= 2*M_PI;
	for(int r=0;r<60;r++)
	{
		// ----check horizontal lines
		dof = 0;
		float disH = 100000, hx=pos.x, hy=pos.y;
		float aTan = 1/tan(ra);
		if (ra < M_PI)
		{
			ry = (((int) pos.y >> 6) << 6) -0.0001;
			rx = (pos.y - ry) * aTan + pos.x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra > M_PI)
		{
			ry = (((int) pos.y >> 6) << 6) + 64;
			rx = (pos.y - ry) * aTan + pos.x;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == M_PI) 
		{
			rx = pos.x;
			ry = pos.y;
			dof = map->max_width;
		}
		while (dof < map->max_height)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			if (my < map->max_height && mx < map->max_width && map->map_arr[my][mx] == '1')
			{
				dof = map->max_height;
				hx = rx;
				hy = ry;
				disH = dist(pos.x, pos.y, hx, hy);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}

		// ----check vertical lines
		dof = 0;
		float disV = 100000, vx=pos.x, vy=pos.y;
		float nTan = tan(ra);
		if (ra < M_P2 || ra > M_P3)
		{
			rx = (((int) pos.x >> 6) << 6) + 64;
			ry = (pos.x - rx) * nTan + pos.y;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra > M_P2 && ra < M_P3)
		{
			rx = (((int) pos.x >> 6) << 6) -0.0001;
			ry = (pos.x - rx) * nTan + pos.y;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == M_PI) 
		{
			rx = pos.x;
			ry = pos.y;
			dof = map->max_width;
		}
		while (dof < map->max_height)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			if (my < map->max_height && mx < map->max_width && map->map_arr[my][mx] == '1')
			{
				dof = map->max_height;
				vx = rx;
				vy = ry;
				disV = dist(pos.x, pos.y, vx, vy);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
		}
		if (disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH;
		}
		dx = rx - pos.x;
		dy = ry - pos.y;
		int	pixels = sqrt(pow(dx, 2) + pow(dy, 2));
		dx /= pixels;
		dy /= pixels;
		double		pixel_x = pos.x;
		double		pixel_y = pos.y;
		while (pixels)
		{
			if (pixel_x <= 0 || pixel_x > app->screen->width)
			{
				break;
			}
			if (pixel_y <= 0 || pixel_y > app->screen->height)
			{
				break;
			}
			my_mlx_pixel_put(app->screen->img, pixel_x, pixel_y, color);
			pixel_x += dx;
			pixel_y += dy;
			--pixels;
		}
		// ----Draw 3d Walls
		// int mapS = map->max_height * map->max_width;
		// float ca = pa-ra;
		// if (ca < 0)
		// 	ca += 2 * M_PI;
		// if (ca > 2 * M_PI)
		// 	ca -= 2 * M_PI;
		// disT = disT * cos(ca); //fisheye fix
		// float lineH = ((((64 * WIN_WIDTH) / 320) * WIN_WIDTH) / disT); //line height
		// if (lineH > WIN_WIDTH)
		// 	lineH = WIN_WIDTH;
		// int a = -1;
		// int b;
		// while (a < WIN_WIDTH)
		// {
		// 	float off = WIN_HEIGHT/2 - lineH/2;
		// 	b = off;
		// 	while (b < (WIN_HEIGHT - off))
		// 	{
		// 		my_mlx_pixel_put(app->screen->img, a, b, color);
		// 		b++;
		// 	}
		// 	a++;
		// }
		ra -= DR;
		if (ra < 0)
			ra += 2*M_PI;
		if (ra > 2*M_PI)
			ra -= 2*M_PI;
	}
}

// Draws line from pixel begin to end
void	draw_facing_ray(t_app *app, t_float_p begin, t_float_p end)
{
	u_int32_t	color;
	double		dx;
	double		dy;

	end.x = begin.x + end.x * 5;
	end.y = begin.y + end.y * 5;
	color = create_trgb(255, 0, 0, 255);
	// To get the direction of the line in 2D space, you can end - begin
	dx = end.x - begin.x; // 10
	dy = end.y - begin.y; // 0

	// From this, we can approximate the number of pixels we’ll have to draw along the way.
	int			pixels = sqrt(pow(dx, 2) + pow(dy, 2));
	// pixels = sqrt((10 * 10) + (0 * 0)) = sqrt(100) = 10

	// The reason why we used double was so we can divide the total distance of our line by the amount of pixels we’ll have to draw.
	dx /= pixels; // 1
	dy /= pixels; // 0

	// So we can finally start plotting the line with a very simple loop
	double		pixel_x = begin.x;
	double		pixel_y = begin.y;
	while (pixels)
	{
		my_mlx_pixel_put(app->screen->img, pixel_x, pixel_y, color);
		// mlx_pixel_put(mlx, win, pixel_x, pixel_y, color);
		pixel_x += dx;
		pixel_y += dy;
		--pixels;
	}
}

void	draw_torches(t_app *app)
{
	size_t	i;
	t_int_p	pixel;

	if (app->game->torches)
	{
		i = -1;
		while (++i < app->game->n_torches)
		{
			pixel.x = app->game->torches[i].pos.x;
			pixel.y = app->game->torches[i].pos.y;
			draw_circle(app->screen->img, pixel, create_trgb(255, 255, 255, 0));
		}
	}
}

void	draw_player(t_app *app)
{
	t_entity	player;
	t_int_p		pixel;

	player = app->game->player;
	pixel.x = player.pos.x;
	pixel.y = player.pos.y;

	draw_circle(app->screen->img, pixel, create_trgb(255, 0, 0, 255));
	draw_facing_ray(app, player.pos, player.delta);
	draw_rays(app, player.pos, player.facing);
}

void	draw_entities(t_app *app)
{
	draw_player(app);
	draw_torches(app);
}

int	draw2d(t_app *app)
{
	//render
	//draw_background <- draw_2d_background
	//draw_walls <- draw_rays
	//draw_minimap <- draw_map + draw_entities
	draw_2d_background(app);
	draw_map(app);
	draw_entities(app);
	my_mlx_put_image_to_window(app);
	// printf("facing: %f\n", app->game->player.facing / M_PI);
	// printf("delta->x: %f\n", app->game->player.delta.x);
	// printf("delta->y: %f\n", app->game->player.delta.y);
	return (1);
}
