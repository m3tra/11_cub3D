/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:01:44 by fheaton-          #+#    #+#             */
/*   Updated: 2023/06/16 16:45:21 by fheaton-         ###   ########.fr       */
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
	// (*tex)[i] = NULL;
	return (1);
}

int	load_tex(void *mlx, int ***texture, char *path)
{
	t_img		tmp;
	int			img_height;
	int			img_width;

	tmp.img = mlx_xpm_file_to_image(mlx, path, &img_width, &img_height);
	if (!tmp.img)
		return (-1);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.line_len, &tmp.endian);
	if (texture_init(texture))
		voidp_to_matrix(tmp, texture, img_height, img_width);
	mlx_destroy_image(mlx, tmp.img);
	if (!*texture)
		return (-1);
	return (1);
}

int	load_elements(void *mlx, t_tex *tex, int id)
{
	int			ret;

	ret = 0;
	if (id == 'N' && !tex->n_wall)
		ret = load_tex(mlx, &tex->n_wall, NO_tex);
	else if (id == 'S' && !tex->s_wall)
		ret = load_tex(mlx, &tex->s_wall, SO_tex);
	else if (id == 'E' && !tex->e_wall)
		ret = load_tex(mlx, &tex->e_wall, EA_tex);
	else if (id == 'W' && !tex->w_wall)
		ret = load_tex(mlx, &tex->w_wall, WE_tex);
	else
		return (-1);
	if (ret < 0)
		return (ret);
	return (tex->n_wall && tex->s_wall && tex->e_wall && tex->w_wall);
}

int		get_tex(t_game *game, void *mlx)
{
	int ret;

	ret = 0;
	ret = load_elements(mlx, game->textures, 'N');
	ret = load_elements(mlx, game->textures, 'S');
	ret = load_elements(mlx, game->textures, 'E');
	ret = load_elements(mlx, game->textures, 'W');
	return (ret);
}
