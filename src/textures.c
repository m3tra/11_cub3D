/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:01:44 by fheaton-          #+#    #+#             */
/*   Updated: 2023/06/13 11:33:42 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	voidp_to_matrix(t_img tmp, int ***texture, int height, int width)
{
	int				x;
	int				y;
	unsigned char	*c;

	if (*texture)
	{
		y = -1;
		while (++y < height)
		{
			x = -1;
			while (++x < width)
			{
				c = (unsigned char *)tmp.addr + (y * tmp.line_len + (x *
				(tmp.bpp / 8)));
				(*texture)[y][x] = (unsigned int)c[3] << 24 | c[2] << 16
					| c[1] << 8 | c[0];
			}
		}
	}
}

int	texture_init(int ***tex)
{
	int	i;

	*tex = ft_calloc(TEXTURE_SIZE + 1, sizeof(int *));
	if (!*tex)
		return (0);
	i = 0;
	while (i < TEXTURE_SIZE)
	{
		(*tex)[i] = ft_calloc(TEXTURE_SIZE, sizeof(int));
		if (!(*tex)[i])
		{
			free_matrix((void **)*tex, NULL);
			return (0);
		}
		i++;
	}
	(*tex)[i] = NULL;
	return (1);
}

int		load_tex(void *mlx, int	***texture, char id)
{
	t_img		tmp;
	int			img_height;
	int			img_width;

	if (id == 'N')
		tmp.img = mlx_xpm_file_to_image(mlx, NO_tex, &img_width, &img_height);
	if (id == 'S')
		tmp.img = mlx_xpm_file_to_image(mlx, SO_tex, &img_width, &img_height);
	if (id == 'W')
		tmp.img = mlx_xpm_file_to_image(mlx, WE_tex, &img_width, &img_height);
	if (id == 'E')
		tmp.img = mlx_xpm_file_to_image(mlx, EA_tex, &img_width, &img_height);
	if (!tmp.img)
		return(-1);
	if (texture_init(texture))
		voidp_to_matrix(tmp, texture, img_height, img_width);
	mlx_destroy_image(mlx, tmp.img);
	if (!*texture)
		return (-1);
	return (1);
}

int		get_tex(t_game *game, void *mlx)
{
	int ret;

	ret = 0;
	ret = load_tex(mlx, &game->textures->n_wall, 'N');
	ret = load_tex(mlx, &game->textures->s_wall, 'S');
	ret = load_tex(mlx, &game->textures->w_wall, 'W');
	ret = load_tex(mlx, &game->textures->e_wall, 'E');
	return (ret);
}
