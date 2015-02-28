/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <llaffile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 17:52:21 by llaffile          #+#    #+#             */
/*   Updated: 2015/02/28 21:35:59 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void 			updatePosition(t_tile *tile, t_index pos)
{
	tile->x = pos.x;
	tile->y = pos.y;
	return ;
}

t_tile			*new_tile(t_index position, int value)
{
	t_tile	*tile;

	if ((tile = (t_tile *)ft_memalloc(sizeof(t_tile))) == NULL)
		return (NULL);
	tile->x = position.x;
	tile->y = position.y;
	tile->value = value;
	tile->merged = 0;
	return (tile);
}

void			savePosition(t_tile *tile)
{
	tile->previous.x = tile->x;
	tile->previous.y = tile->y;
	return ;
}
