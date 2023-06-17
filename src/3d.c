/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:00:27 by fporto            #+#    #+#             */
/*   Updated: 2023/06/16 16:44:43 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define M_P2	(M_PI/2)
#define M_P3	(3*M_PI/2)
#define DR		0.01745329


// Paints top half of the screen as ceiling_color and bottom half as floor_color
void	draw_3d_background(t_app *app)
{
	t_screen	*screen;
	u_int32_t	floor_color;
	u_int32_t	ceiling_color;
	size_t		x;
	size_t		y;

	screen = app->screen;
	floor_color = app->game->textures->floor_color = create_trgb(F_Color);
	ceiling_color = app->game->textures->ceiling_color = create_trgb(C_Color);
	y = 0;
	while (y < (screen->height / 2))
	{
		x = -1;
		while (++x < screen->width)
			my_mlx_pixel_put(screen->img, x, y, ceiling_color);
		++y;
	}
	while (y < screen->height)
	{
		x = -1;
		while (++x < screen->width)
			my_mlx_pixel_put(screen->img, x, y, floor_color);
		++y;
	}
}

// float degToRad(int a)
// { 
// 	return (a*M_PI/180.0);
// }

// float FixAng(float a)
// {
// 	if(a >= 2*M_PI)
// 		a-=2*M_PI;
// 	if(a < 0)
// 		a+=2*M_PI;
// 	return (a);
// }

// void drawWalls(t_app *app, t_float_p pos, float pa)
// {
// 	int r,mx,my,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH;
// 	t_map		*map;
// 	u_int32_t	color;
// 	int c = 0;
// 	map = app->game->map;
// 	ra=FixAng(pa + (degToRad(FOV)/2));       //ray set back 30 degrees
// 	for(r=0;r<FOV;r++)
// 	{
// 	//---Vertical--- 
// 		dof=0; side=0; disV=100000;
// 		float Tan=tan(ra);
// 		if (cos(ra)> 0.0001) //looking left
// 		{
// 			rx=(((int)pos.x>>6)<<6)+64;
// 			ry=(pos.y-rx)*Tan+pos.y;
// 			xo = 64;
// 			yo = -xo*Tan;
// 		}
// 		else if (cos(ra)<-0.0001) //looking right
// 		{
// 			rx=(((int)pos.x>>6)<<6) -0.0001;
// 			ry=(pos.x-rx)*Tan+pos.y;
// 			xo=-64;
// 			yo=-xo*Tan;
// 		}
// 		else //looking up or down. no hit
// 		{
// 			rx = pos.x;
// 			ry = pos.y;
// 			dof = map->max_width;
// 		}
// 		while(dof < (int)map->max_width)
// 		{
// 			mx = (int)(rx/64);
// 			my = (int)(ry/64);
// 			int var = mx*map->max_height + my;
// 			printf("\nrx: %f\n", rx);
// 			printf("\nry: %f\n", ry);
// 			printf("\nmx: %d\n", mx);
// 			printf("\nmy: %d\n", my);
// 			if (my < (int)map->max_height && my > 0 && mx < (int)map->max_width && mx > 0 && map->map_arr[my][mx] == '1')
// 			{
// 				dof = map->max_width;
// 				disV=cos(ra)*(rx-pos.x) - sin(ra)*(ry-pos.y);
// 			}//hit         
// 			else
// 			{
// 				rx+=xo;
// 				ry+=yo;
// 				dof ++;
// 			}//check next vertical
// 		} 
// 		vx=rx; vy=ry;
// 	//---Horizontal---
// 		dof=0; disH=100000;
// 		Tan=1.0/Tan; 
// 		if (sin(ra) > 0.0001) //looking up
// 		{
// 			ry=(((int)pos.y>>6)<<6) -0.0001;
// 			rx=(pos.y-ry)*Tan+pos.x;
// 			yo=-64;
// 			xo=-yo*Tan;
// 		}
// 		else if (sin(ra) < -0.0001) //looking down
// 		{
// 			ry=(((int)pos.y>>6)<<6)+64;
// 			rx=(pos.y-ry)*Tan+pos.x;
// 			yo= 64;
// 			xo=-yo*Tan;
// 		}
// 		else //looking straight left or right
// 		{
// 			rx=pos.x;
// 			ry=pos.y;
// 			dof = map->max_height;
// 		}
// 		while(dof < (int)map->max_height) 
// 		{
// 			mx=(int)(rx/64);
// 			my=(int)(ry/64);
// 			if(my < (int)map->max_height && my > 0 && mx < (int)map->max_width && mx > 0 && map->map_arr[my][mx] == '1')
// 			{
// 				dof = map->max_height;
// 				disH=cos(ra)*(rx-pos.x)-sin(ra)*(ry-pos.y);
// 			}//hit
// 			else
// 			{
// 				rx+=xo;
// 				ry+=yo;
// 				dof++;
// 			}//check next horizontal
// 		}
// 	// ----Draw 3d Walls
// 		color = create_trgb(255, 255, 0, 0);
// 		if(disV < disH)
// 		{
// 			rx=vx;
// 			ry=vy;
// 			disH=disV;
// 			color = create_trgb(255, 0, 0, 255);
// 		}
// 		int ca = FixAng(pa-ra);
// 		disH = disH*cos(degToRad(ca)); //fix fisheye 
// 		int lineH = (32 * WIN_HEIGHT)/disH;
// 		if(lineH>WIN_HEIGHT)
// 			lineH=WIN_HEIGHT; //line height and limit
// 		int b;
// 		int a = 0;
// 		while (a < (WIN_WIDTH/FOV))
// 		{
// 			float off = WIN_HEIGHT/2 - lineH/2;
// 			b = 0;
// 			while (b < lineH) //draw vertical wall
// 			{
// 				my_mlx_pixel_put(app->screen->img, c, b + off, color);
// 				b++;
// 			}
// 			a++;
// 			c++;
// 		}
// 		// printf("\n%f\n", ra);
// 		ra=FixAng(ra-DR); //go to next ray
// 	}
// }

float dist_3d(float ax, float ay, float bx, float by)
{
	double ret;

	ret = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
	return (ret);
}

double	h_check(t_map *map, double ang, t_check *h, t_float_p pos)
{
	t_float_p	off;

	if (ang > M_PI) //looking up
	{
		h->ry = ((int)pos.y) + 1.0001;
		h->rx = (pos.y - h->ry) * (-1 / tan(ang)) + pos.x;
		off = (t_float_p){.x = -1 * (-1 / tan(ang)), .y = 1};
	}
	else if (ang < M_PI) //looking down
	{
		h->ry = ((int)pos.y) - 0.0001;
		h->rx = (pos.y - h->ry) * (-1 / tan(ang)) + pos.x;
		off = (t_float_p){.x = (-1 / tan(ang)), .y = -1};
	}
	if (ang != 0 && ang != M_PI)
	{
		while (h->ry >= 0 && h->ry < map->max_width
			&& h->rx >= 0 && h->rx < map->max_height)
		{
			if (map->map_arr[(int)h->ry][(int)h->rx] == '1')
				return (h->z = dist_3d(h->rx, h->ry, pos.x, pos.y));
			(void) (t_float_p){(h->rx += off.x), (h->ry += off.y)};
		}
	}
	return (h->z = -1);
}

double v_check(t_map *map, double ang, t_check *v, t_float_p pos)
{
	t_float_p	off;

	if (ang < M_P2 || ang > M_P3) //looking left
	{
		v->rx = ((int)pos.x) - 0.0001;
		v->ry = (pos.x - v->rx) * -tan(ang) + pos.y;
		off = (t_float_p){.x = -1, .y = -tan(ang)};
	}
	else if (ang > M_P2 && ang < M_P3) //looking right
	{
		v->rx = ((int)pos.x) + 1.0001;
		v->ry = (pos.x - v->rx) * (-tan(ang)) + pos.y;
		off = (t_float_p){.x = 1, .y = tan(ang)};
	}
	if (ang != M_P2 && ang != M_P3)
	{
		while (v->ry >= 0 && v->ry < map->max_height
			&& v->rx >= 0 && v->rx < map->max_width)
		{
			if (map->map_arr[(int)v->ry][(int)v->rx] == '1')
				return (v->z = dist_3d(v->rx, v->ry, pos.x, pos.y));
			(void) (t_float_p){v->rx += off.x, v->ry += off.y};
			
		}
	}
	return (v->z = -1);
}

void	aux(double ang, t_check *hv, t_tex *tex, t_check *check)
{
	if ((hv[0].z < hv[1].z && hv[0].z > 0.0) || hv[1].z < 0)
	{
		*check = hv[0];
		check->tex.x = (check->rx - (int)check->rx) * TEXTURE_SIZE;
		check->texture = tex->s_wall;
		if (ang > M_PI)
			check->tex.x = TEXTURE_SIZE - check->tex.x - 1;
		else
			check->texture = tex->n_wall;
	}
	else
	{
		*check = hv[1];
		check->tex.x = (check->ry - (int)check->ry) * TEXTURE_SIZE;
		check->texture = tex->w_wall;
		if (ang > M_P2 && ang < M_P3)
			check->texture = tex->e_wall;
		else
			check->tex.x = TEXTURE_SIZE - check->tex.x - 1;
	}
}

t_check *check_wall(t_tex *tx,t_map *map, t_float_p pos, double ang, float pa)
{
	t_check hv[2];
	t_check *check;

	hv[0] = (t_check){.rx = 0, .ry = 0, .z = 0};
	hv[1] = (t_check){.rx = 0, .ry = 0, .z = 0};
	check = ft_calloc(1, sizeof(t_check));
	h_check(map, ang, &hv[0], pos);
	v_check(map, ang, &hv[1], pos);
	aux(ang, hv, tx, check);
	check->z = check->z * cos(fmod(pa - ang + 2 * M_PI,
				2 * M_PI));
	check->lh = (double)WIN_HEIGHT / check->z;
	check->lo = ((double)WIN_HEIGHT - check->lh) / 2;
	if (check->lo < 0)
		check->texoff = (check->lh - WIN_HEIGHT) / 2.0;
	if (check->lo < 0)
		check->lo = 0;
	check->tex.y = check->texoff * (TEXTURE_SIZE / (double)check->lh);
	return (check);
}

void drawWalls(t_app *app, t_map *map, t_float_p pos, float pa)
{
	t_check		*check;
	double		ang;
	int			a;
	int			b;
	int			c;

	a = -1;
	while (++a < WIN_WIDTH)
	{
		ang = (a * FOV / WIN_WIDTH) - FOV / 2;
		ang = fmod(pa + ang + (2 * M_PI), (2 * M_PI));
		check = check_wall(app->game->textures, map, pos, ang, pa);
		b = check->lo -1;
		while (++b < WIN_HEIGHT && b < check->lh + check->lo)
		{
			c = -1;
			while (++c < 1)
			{
				// printf("\n%d\n", check->texture[(int)check->tex.y][(int)(check->tex.x)]);
				my_mlx_pixel_put2(app->screen->img, a + c, b,
					check->texture[(int)check->tex.y][(int)(check->tex.x)]);
			}
			check->tex.y += TEXTURE_SIZE / (double)check->lh;
			(check->tex.y >= TEXTURE_SIZE) && (check->tex.y = TEXTURE_SIZE - 1);
		}
	}
}

float	fix_angle(float pa)
{
	if (pa < M_PI)
		pa = M_P2 - (pa - M_P2);
	else if (pa < M_P3)
		pa = 2 * M_PI - (pa - M_PI);
	else
		pa = M_PI + (2 * M_PI - pa);
	return (pa);
}

int	draw3d(t_app *app)
{
	float pa;
	
	pa = fix_angle(app->game->player.facing);
	draw_3d_background(app);
	drawWalls(app, app->game->map,
		app->game->player.pos, pa);
	draw2d(app);
	my_mlx_put_image_to_window(app);
	return (1);
}
