/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:48:00 by fporto            #+#    #+#             */
/*   Updated: 2023/03/15 15:00:11 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

// # include "cub3d.h"

# define TILE_SIZE 64

# ifndef BONUS
#  define MAP_CHARS		" 01NSWE"
# else
#  define MAP_CHARS		" 01NSWEDT"
# endif

# define EMPTY			'0'
# define WALL			'1'
# define PLAYER_DIR_N	'N'
# define PLAYER_DIR_S	'S'
# define PLAYER_DIR_W	'W'
# define PLAYER_DIR_E	'E'
# define DOOR			'D'
# define TORCH			'T'

// TEXTURES

// Enemies
# define ENEMIES_TEXTURES	"./textures/xpm/enemies/"

// Map (Walls/Doors)
# define MAP_TEXTURES		"./textures/xpm/map/"

#endif
