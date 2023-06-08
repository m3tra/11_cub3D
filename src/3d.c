/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:00:27 by fporto            #+#    #+#             */
/*   Updated: 2023/06/07 23:10:11 by fheaton-         ###   ########.fr       */
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
	floor_color = app->game->textures->floor_color = create_trgb(255, 85, 85, 85);
	ceiling_color = app->game->textures->ceiling_color = create_trgb(255, 50, 50, 50);
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
	return (sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}

t_check	h_check(t_map *map, double ang, t_float_p pos)
{
	t_check	c;

	if (ang > M_PI) //looking down
	{
		c.ry = ((int)pos.y) + 64;
		c.rx = (pos.y - c.ry) * (-1 / tan(ang)) + pos.x;
		c.yo = 64;
		c.xo = -c.yo * (-1 / tan(ang));
	}
	else if (ang < M_PI) //looking up
	{
		c.ry = ((int)pos.y) - 0.0001;
		c.rx = (pos.y - c.ry) * (-1 / tan(ang)) + pos.x;
		c.yo = -64;
		c.xo = -c.yo * (-1 / tan(ang));
	}
	if (ang != 0 && ang != M_PI)
	{
		// printf("\nhry: %f\n", c.ry);
		// printf("\nhrx: %f\n", c.rx);
		while (c.ry >= 0 && c.ry/64 < map->max_height
			&& c.rx >= 0 && c.rx/64 < map->max_width)
		{
			if (map->map_arr[(int)c.ry/64][(int)c.rx/64] == '1')
				c.z = dist_3d(c.rx, c.ry, pos.x, pos.y);
			if (map->map_arr[(int)c.ry/64][(int)c.rx/64] == '1')
				return(c);
			c.rx += c.xo;
			c.ry += c.yo;
		}
	}
	c.z = -1;
	return (c);
}

t_check v_check(t_map *map, double ang, t_float_p pos)
{
	t_check	c;

	if (ang < M_P2 || ang > M_P3) //looking right
	{
		c.rx = ((int)pos.x) - 0.0001;
		c.ry = (pos.x - c.rx) * tan(ang) + pos.y;
		c.xo = -64;
		c.yo = -c.xo * tan(ang);
	}
	else if (ang > M_P2 && ang < M_P3) //looking left
	{
		c.rx = ((int)pos.x) + 64;
		c.ry = (pos.x - c.rx) * (-tan(ang)) + pos.y;
		c.xo = 64;
		c.yo = c.xo * tan(ang);
	}
	if (ang != M_P2 && ang != M_P3)
	{
		// printf("\nvry: %f\n", c.ry);
		// printf("\nvrx: %f\n", c.rx);
		while (c.ry >= 0 && c.ry/64 < map->max_height
			&& c.rx >= 0 && c.rx/64 < map->max_width)
		{
			if (map->map_arr[(int)c.ry/64][(int)c.rx/64] == '1')
				c.z = dist_3d(c.rx, c.ry, pos.x, pos.y);
			if (map->map_arr[(int)c.ry/64][(int)c.rx/64] == '1')
				return(c);
			c.rx += c.xo;
			c.ry += c.yo;
		}
	}
	c.z = -1;
	return (c);
}

t_check	aux(t_check h, t_check v)
{
	if ((h.z < v.z && h.z > 0.0) || v.z < 0)
	{
		h.color = create_trgb(255, 255, 0, 0);
		// check->tex.x = (check->x - (int)check->x) * TEXTURE_SIZE;
		// check->texture = textures.so;
		// if (ang > M_PI)
		// 	check->tex.x = TEXTURE_SIZE - check->tex.x - 1;
		// else
		// 	check->texture = textures.no;
		return (h);
	}
	else
	{
		v.color = create_trgb(255, 255, 0, 0);
		// check->tex.x = (check->y - (int)check->y) * TEXTURE_SIZE;
		// check->texture = textures.we;
		// if (ang > M_PI_2 && ang < M_PI_2 * 3)
		// 	check->texture = textures.ea;
		// else
		// 	check->tex.x = TEXTURE_SIZE - check->tex.x - 1;
		return (v);
	}
}

t_check check_wall(t_map *map, t_float_p pos, double ang, float pa)
{
	t_check h;
	t_check v;
	t_check check;

	h = h_check(map, ang, pos);
	v = v_check(map, ang, pos);
	check = aux(h, v);
	check.z = check.z * cos(fmod(pa - ang + 2 * M_PI,
				2 * M_PI));
	printf("\ncheck z: %d\n", check.z);
	check.lh = (double)WIN_HEIGHT / check.z;
	check.lo = ((double)WIN_HEIGHT - check.lh) / 2;
	if (check.lo < 0)
		check.texoff = (check.lh - WIN_HEIGHT) / 2.0;
	if (check.lo < 0)
		check.lo = 0;
	// check->tex.y = check->texoff * (TEXTURE_SIZE / (double)check->lh);
	return (check);
}

void drawWalls(t_app *app, t_float_p pos, float pa)
{
	t_map		*map;
	double		ang;
	t_check		check;
	int			a;
	int			b;
	int			c;

	map = app->game->map;
	a = -1;
	while (++a < WIN_WIDTH)
	{
		ang = (a * FOV / WIN_WIDTH) - FOV / 2;
		ang = fmod(pa + ang + (2 * M_PI), (2 * M_PI));
		check = check_wall(map, pos, ang, pa);
		b = check.lo -1;
		printf("\nlh: %f\n", check.lh);
		printf("\nlo: %f\n", check.lo);
		while (++b < WIN_WIDTH && b < check.lh + check.lo)
		{
			c = -1;
			while (++c)
				my_mlx_pixel_put(app->screen->img, a + c, b, check.color);
		}
	}
}


int	draw3d(t_app *app)
{
	draw_3d_background(app);
	drawWalls(app, app->game->player.pos, app->game->player.facing);
	

	my_mlx_put_image_to_window(app);
	return (1);
}
