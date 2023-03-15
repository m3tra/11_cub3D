/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:19 by fporto            #+#    #+#             */
/*   Updated: 2023/03/14 04:30:03 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Prints how to run program to stdout
static void	usage(void)
{
	printf("Usage:\n");
	printf("\t./cub3D {map file}\n");
	printf("\t(Map file must have .cub extension)\n");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_app	*app;

	if (argc != 2)
		usage();

	check_macros();

	app = init_app(argv[1]);

	setup_mlx_hooks(app);
	mlx_loop(app->mlx);
	return (0);
}
