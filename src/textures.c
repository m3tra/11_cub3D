/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:01:44 by fheaton-          #+#    #+#             */
/*   Updated: 2023/06/18 08:25:03 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	voidp_to_matrix(t_img *tmp, int **texture, int height, int width)
{
	int				x;
	int				y;
	unsigned char	*c;

	if (texture)
	{
		y = -1;
		while (++y < height)
		{
			x = -1;
			while (++x < width)
			{
				c = (unsigned char *)tmp->addr + (y * tmp->line_len + (x * \
					(tmp->bpp / 8)));
				texture[y][x] = (unsigned int)(c[3] << 24 | c[2] << 16 \
					| c[1] << 8 | c[0]);
			}
		}
	}
}

int	**texture_init(void)
{
	int		**tex;
	int		y;

	tex = ft_calloc(TEXTURE_SIZE + 1, sizeof(int *));
	if (!tex)
		err_exit("Failed ft_calloc @texture_init", NULL);
	y = -1;
	while (++y < TEXTURE_SIZE)
	{
		tex[y] = ft_calloc(TEXTURE_SIZE, sizeof(int));
		if (!tex[y])
		{
			free_matrix((void **)tex);
			err_exit("Failed ft_calloc @texture_init", NULL);
		}
	}
	return (tex);
}

int	**load_tex(void *mlx, char *path)
{
	int		**texture;
	t_img	*tmp;
	int		img_height;
	int		img_width;

	if (!path)
		err_exit("Missing path @load_tex", NULL);
	tmp = ft_calloc(1, sizeof(t_img));
	if (!tmp)
		err_exit("Failed ft_calloc @load_tex", NULL);
	tmp->img = mlx_xpm_file_to_image(mlx, path, &img_width, &img_height);
	if (!tmp->img)
		err_exit("Failed mlx_xpm_file_to_image @load_tex", NULL);
	tmp->addr = my_mlx_get_data_addr(tmp);
	texture = texture_init();
	voidp_to_matrix(tmp, texture, img_height, img_width);
	mlx_destroy_image(mlx, tmp->img);
	ft_free(tmp);
	if (!texture)
		err_exit("Failed to load texture @load_tex", NULL);
	return (texture);
}

void	load_textures(t_app *app)
{
	t_tex	*tex;

	tex = app->game->textures;
	tex->n_wall = load_tex(app->mlx, tex->n_wall_path);
	tex->s_wall = load_tex(app->mlx, tex->s_wall_path);
	tex->w_wall = load_tex(app->mlx, tex->w_wall_path);
	tex->e_wall = load_tex(app->mlx, tex->e_wall_path);
}
