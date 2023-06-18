/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 07:57:11 by fheaton-          #+#    #+#             */
/*   Updated: 2023/06/18 08:42:51 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	dist_3d(float ax, float ay, float bx, float by)
{
	double	ret;

	ret = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
	return (ret);
}

double	h_check(t_map *map, double ang, t_check *h, t_float_p pos)
{
	h->off.x = 0;
	h->off.y = 0;
	if (ang > M_PI)
	{
		h->ry = ((int)pos.y) + 1.0001;
		h->rx = (pos.y - h->ry) * (-1 / tan(ang)) + pos.x;
		h->off = (t_float_p){.x = -1 * (-1 / tan(ang)), .y = 1};
	}
	else if (ang < M_PI)
	{
		h->ry = ((int)pos.y) - 0.0001;
		h->rx = (pos.y - h->ry) * (-1 / tan(ang)) + pos.x;
		h->off = (t_float_p){.x = (-1 / tan(ang)), .y = -1};
	}
	if (ang != 0 && ang != M_PI)
	{
		while (h->ry >= 0 && h->ry < map->max_height
			&& h->rx >= 0 && h->rx < map->max_width)
		{
			if (map->map_arr[(int)h->ry][(int)h->rx] == '1')
				return (h->z = dist_3d(h->rx, h->ry, pos.x, pos.y));
			(void) (t_float_p){(h->rx += h->off.x), (h->ry += h->off.y)};
		}
	}
	return (h->z = -1);
}

double	v_check(t_map *map, double ang, t_check *v, t_float_p pos)
{
	v->off.y = 0;
	if (ang < (M_PI / 2) || ang > (3 * M_PI / 2))
	{
		v->rx = ((int)pos.x) - 0.0001;
		v->ry = (pos.x - v->rx) * -tan(ang) + pos.y;
		v->off = (t_float_p){.x = -1, .y = -tan(ang)};
	}
	else if (ang > (M_PI / 2) && ang < (3 * M_PI / 2))
	{
		v->rx = ((int)pos.x) + 1.0001;
		v->ry = (pos.x - v->rx) * (-tan(ang)) + pos.y;
		v->off = (t_float_p){.x = 1, .y = tan(ang)};
	}
	if (ang != (M_PI / 2) && ang != (3 * M_PI / 2))
	{
		while (v->ry >= 0 && (int)v->ry < map->max_height
			&& v->rx >= 0 && (int)v->rx < map->max_width)
		{
			if (map->map_arr[(int)v->ry][(int)v->rx] == '1')
				return (v->z = dist_3d(v->rx, v->ry, pos.x, pos.y));
			(void) (t_float_p){v->rx += v->off.x, v->ry += v->off.y};
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
		if (ang > (M_PI / 2) && ang < (3 * M_PI / 2))
			check->texture = tex->e_wall;
		else
			check->tex.x = TEXTURE_SIZE - check->tex.x - 1;
	}
}

t_check	*check_wall(t_game *g, t_float_p pos, double ang, float pa)
{
	t_check	hv[2];
	t_check	*check;

	hv[0] = (t_check){.rx = 0, .ry = 0, .z = 0};
	hv[1] = (t_check){.rx = 0, .ry = 0, .z = 0};
	check = ft_calloc(1, sizeof(t_check));
	h_check(g->map, ang, &hv[0], pos);
	v_check(g->map, ang, &hv[1], pos);
	aux(ang, hv, g->textures, check);
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
