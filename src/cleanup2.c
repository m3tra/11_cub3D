/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:02:15 by fheaton-          #+#    #+#             */
/*   Updated: 2023/06/13 11:02:32 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_matrix(void **matrix, void (*del)(void *))
{
	int	i;

	if (!matrix || !del)
		return ;
	i = -1;
	while (matrix[++i])
		del(matrix[i]);
	free(matrix);
}
