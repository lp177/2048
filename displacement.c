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

short	move_left(t_game *g)
{
	short	have_move;
	short 	merge;
	int		x;
	int		y;

	have_move = 0;
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
			have_move = 1;
			if (g->tiles[y][x - 1]->value == 0)
			{
				g->tiles[y][x - 1]->value = g->tiles[y][x]->value;
				g->tiles[y][x]->value = 0;
			}
			else if (g->tiles[y][x]->value == g->tiles[y][x - 1]->value)
			{
				g->tiles[y][x - 1]->value *= 2;
				g->tiles[y][x]->value = 0;
				merge = 1;
			}
		}
	}
	return (have_move);
}

short	move_right(t_game *g)
{
	short	have_move;
	short 	merge;
	int		x;
	int		y;

	have_move = 0;
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
			have_move = 1;
			if (g->tiles[y][x + 1]->value == 0)
			{
				g->tiles[y][x + 1]->value = g->tiles[y][x]->value;
				g->tiles[y][x]->value = 0;
			}
			else if (g->tiles[y][x + 1]->value == g->tiles[y][x]->value)
			{
				g->tiles[y][x + 1]->value *= 2;
				g->tiles[y][x]->value = 0;
				merge = 1;
			}
		}
	}
	return (have_move);
}

short	move_up(t_game *g)
{
	short	have_move;
	short 	merge;
	int		x;
	int		y;

	have_move = 0;
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
			have_move = 1;
			if (g->tiles[y - 1][x]->value == 0)
			{
				g->tiles[y - 1][x]->value = g->tiles[y][x]->value;
				g->tiles[y][x]->value = 0;
			}
			else if (g->tiles[y - 1][x]->value == g->tiles[y][x]->value)
			{
				g->tiles[y - 1][x]->value *= 2;
				g->tiles[y][x]->value = 0;
				merge = 1;
			}
		}
	}
	return (have_move);
}

short	move_down(t_game *g)
{
	short	have_move;
	short 	merge;
	int		x;
	int		y;

	have_move = 0;
	x = -1;
	while (g->tiles[0][++x])
	{
		merge = 0;
		y = -1;
		while (g->tiles[++y] && g->tiles[y][x])
		{
			if (g->tiles[y][x]->value < 1 || !g->tiles[y + 1] || !g->tiles[y + 1][x])
				continue;
			if (g->tiles[y + 1][x]->value > 0 && merge)
				continue ;
			have_move = 1;
			if (g->tiles[y + 1][x]->value == 0)
			{
				g->tiles[y + 1][x]->value = g->tiles[y][x]->value;
				g->tiles[y][x]->value = 0;
			}
			else if (g->tiles[y + 1][x]->value == g->tiles[y][x]->value)
			{
				g->tiles[y + 1][x]->value *= 2;
				g->tiles[y][x]->value = 0;
				merge = 1;
			}
		}
	}
	return (have_move);
}

t_tile	*take_n_empty(t_game *g, int n)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	y = -1;
	while (g->tiles[++y])
	{
		x = -1;
		while (g->tiles[y][++x])
		{
			if (g->tiles[y][x]->value < 1)
				i++;
			if (n == i)
				return (g->tiles[y][x]);
		}
	}
	return (NULL);
}

int		count_empty_tiles(t_game *g)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	y = -1;
	while (g->tiles[++y])
	{
		x = -1;
		while (g->tiles[y][++x])
		{
			if (g->tiles[y][x]->value < 1)
				i++;
			else if (g->tiles[y][x]->value > WIN_VALUE)
			{
				ft_putstr("\nYou win.");
				ft_error("\nYou win.");
			}
		}
	}
	return (i);
}

void	gen_num(t_game *g)
{
	t_tile	*target;
	int		empty;
	time_t	t;

	ft_putstrerrno("\n\n !! Gen ennemy\n");
	if ((empty = count_empty_tiles(g)) < 2)
	{
		ft_putstr("\nYou loose.");
		ft_error("\nYou loose.");
	}
	srand((unsigned) time(&t));
	empty = rand() % empty;
	if ((target = take_n_empty(g, empty)))
		target->value = 2;
	ft_putstrerrno("\n\n !! End gen ennemy\n");
}

void	displacement(t_game *g, int c)
{
	short	have_move;

	have_move = 0;
	if (c == KEY_LEFT)
	{
		ft_putstrerrno("\n\n == KEY_LEFT\n");
		have_move = move_left(g);
	}
	else if (c == KEY_RIGHT)
	{
		ft_putstrerrno("\n\n == KEY_RIGHT\n");
		have_move = move_right(g);
	}
	else if (c == KEY_UP)
	{
		ft_putstrerrno("\n\n == KEY_UP\n");
		have_move = move_up(g);
	}
	else if (c == KEY_DOWN)
	{
		ft_putstrerrno("\n\n == KEY_DOWN\n");
		have_move = move_down(g);
	}
	redraw(g);
	resize(g);
	if (have_move)
		gen_num(g);
	redraw(g);
}