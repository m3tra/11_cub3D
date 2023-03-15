/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:04:36 by fporto            #+#    #+#             */
/*   Updated: 2023/03/13 07:08:47 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
