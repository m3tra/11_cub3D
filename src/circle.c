/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:04:36 by fporto            #+#    #+#             */
/*   Updated: 2023/06/18 07:58:59 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle2(t_img *img, int xo, int yo, u_int32_t	color)
{
	int	radius;
	int	x;
	int	y;

	radius = CIRCLE_RADIUS;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (pow(x, 2) + pow(y, 2) - radius < 0)
				my_mlx_pixel_put(img, x + xo, y + yo, color);
			x++;
		}
		y++;
	}
}

void	draw_circle(t_img *img, t_int_p pixel, u_int32_t	color)
{
	int	radius;
	int	x;
	int	y;

	radius = CIRCLE_RADIUS;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (pow(x, 2) + pow(y, 2) - radius < 0)
				my_mlx_pixel_put(img, x + pixel.x, y + pixel.y, color);
			x++;
		}
		y++;
	}
}
