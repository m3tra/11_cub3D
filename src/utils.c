/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 02:40:57 by fporto            #+#    #+#             */
/*   Updated: 2023/06/16 16:31:31 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Prints specified error message to stdout and exits the program
void	err_exit(const char *err, t_app *app)
{
	ft_putstr_fd(RED"Error\n"WHITE, 2);
	ft_putstr_fd(err, 2);
	ft_putchar_fd('\n', 2);
	if (app)
	{
		app->status_code = 1;
		stop(app);
	}
	exit(EXIT_FAILURE);
}

// Exit the program
int	stop(void *param)
{
	t_app	*app;
	int		status_code;

	app = (t_app *)param;
	if (app)
		status_code = app->status_code;
	else
		status_code = 1;
	free_app(app);
	exit(status_code);
	return (1);
}

// Associate keyboard presses with specific function calls
static int	key_handler(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keycode == MLX_KEY_ESC)
		stop(app);
	else if (keycode == MLX_KEY_W || \
			keycode == MLX_KEY_S ||
			keycode == MLX_KEY_A || \
			keycode == MLX_KEY_D)
		move(app, keycode);
	else if (keycode == MLX_KEY_LEFT || \
			keycode == MLX_KEY_RIGHT)
		rotate_view(app, keycode);
	return (1);
}

// Registers user event handling
void	setup_mlx_hooks(t_app *app)
{
	mlx_hook(app->screen->win, 17, (1L << 17), stop, app);
	mlx_key_hook(app->screen->win, key_handler, app);
	// if (DIMENTIONS == 2)
	// 	mlx_loop_hook(app->mlx, draw2d, app);
	// else
	mlx_loop_hook(app->mlx, draw3d, app);
}
