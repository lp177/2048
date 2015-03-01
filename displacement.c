/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displacement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luperez <luperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 23:57:31 by luperez           #+#    #+#             */
/*   Updated: 2015/02/28 05:00:10 by luperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	move_left(t_game *g)
{
	short 	merge;
	int		x;
	int		y;

	y = -1;
	while (g->tiles[++y])
	{
		merge = 0;
		x = g->tile_size;
		while (--x != -1 && g->tiles[y][x])
		{
			if (g->tiles[y][x]->value < 1 || x == 0 || !g->tiles[y][x - 1])
				continue;
			if (g->tiles[y][x - 1]->value > 0 && merge)
				continue ;
			if (g->tiles[y][x - 1]->value == 0)
			{
				g->tiles[y][x - 1]->value = g->tiles[y][x]->value;
				g->tiles[y][x]->value = 0;
			}
			else
			{
				g->tiles[y][x - 1]->value += g->tiles[y][x]->value;
				g->tiles[y][x]->value = 0;
				merge = 1;
			}
		}
	}
}

void	move_right(t_game *g)
{
	short 	merge;
	int		x;
	int		y;

	y = -1;
	while (g->tiles[++y])
	{
		merge = 0;
		x = -1;
		while (g->tiles[y][++x])
		{
			if (g->tiles[y][x]->value < 1 || !g->tiles[y][x + 1])
				continue;
			if (g->tiles[y][x + 1]->value > 0 && merge)
				continue ;
			if (g->tiles[y][x + 1]->value == 0)
			{
				g->tiles[y][x + 1]->value = g->tiles[y][x]->value;
				g->tiles[y][x]->value = 0;
			}
			else
			{
				g->tiles[y][x + 1]->value += g->tiles[y][x]->value;
				g->tiles[y][x]->value = 0;
				merge = 1;
			}
		}
	}
}

void	move_up(t_game *g)
{
	short 	merge;
	int		x;
	int		y;

	x = -1;
	while (g->tiles[0][++x])
	{
		merge = 0;
		y = g->tile_size;
		while (--y != -1 && g->tiles[y][x])
		{
			if (g->tiles[y][x]->value < 1 || y == 0 || !g->tiles[y - 1][x])
				continue;
			if (g->tiles[y - 1][x]->value > 0 && merge)
				continue ;
			if (g->tiles[y - 1][x]->value == 0)
			{
				g->tiles[y - 1][x]->value = g->tiles[y][x]->value;
				g->tiles[y][x]->value = 0;
			}
			else
			{
				g->tiles[y - 1][x]->value += g->tiles[y][x]->value;
				g->tiles[y][x]->value = 0;
				merge = 1;
			}
		}
	}
}

void	move_down(t_game *g)
{
	short 	merge;
	int		x;
	int		y;

ft_putstr("\n\n=====\nMove down\n====\n\n");
	x = -1;
	while (g->tiles[0][++x])
	{
		merge = 0;
		y = -1;
		while (g->tiles[++y] && g->tiles[++y][x])
		{
			if (g->tiles[y][x]->value < 1 || !g->tiles[y + 1][x])
				continue;
			if (g->tiles[y + 1][x]->value > 0 && merge)
				continue ;
			if (g->tiles[y + 1][x]->value == 0)
			{
				g->tiles[y + 1][x]->value = g->tiles[y][x]->value;
				g->tiles[y][x]->value = 0;
			}
			else
			{
				g->tiles[y + 1][x]->value += g->tiles[y][x]->value;
				g->tiles[y][x]->value = 0;
				merge = 1;
			}
		}
	}
}

void	displacement(t_game *g, int c)
{
	if (c == KEY_LEFT)
		move_left(g);
	else if (c == KEY_RIGHT)
		move_right(g);
	else if (c == KEY_UP)
		move_up(g);
	else if (c == KEY_DOWN)
		move_down(g);
	redraw(g);
}