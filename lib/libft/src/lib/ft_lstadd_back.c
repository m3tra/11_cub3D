/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:57:45 by fporto            #+#    #+#             */
/*   Updated: 2023/03/08 15:44:01 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_item)
{
	if (!lst)
		return;
	if (*lst == NULL)
		*lst = new_item;
	else
		ft_lstlast(*lst)->next = new_item;
}
