/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:02:05 by fporto            #+#    #+#             */
/*   Updated: 2023/03/10 15:57:46 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns ARGB value as unsigned int
u_int32_t	create_trgb(u_int32_t t, u_int32_t r, u_int32_t g, u_int32_t b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// Returns transparency value
u_int32_t	get_t(u_int32_t trgb)
{
	return ((trgb >> 24) & 0xFF);
}

// Returns red value
u_int32_t	get_r(u_int32_t trgb)
{
	return ((trgb >> 16) & 0xFF);
}

// Returns green value
u_int32_t	get_g(u_int32_t trgb)
{
	return ((trgb >> 8) & 0xFF);
}

// Returns blue value
u_int32_t	get_b(u_int32_t trgb)
{
	return (trgb & 0xFF);
}
