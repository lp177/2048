/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luperez <luperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 23:57:31 by luperez           #+#    #+#             */
/*   Updated: 2015/02/28 05:00:10 by luperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	borders(t_window *win)
{
	int	x;
	int	y;
	int	i;

	x = win->x + win->w - 1;
	y = win->y + win->h - 1;
	i = -1;
	while (++i <= y)
	{
		mvprintw(win->y + i, win->x, "  ");
		mvprintw(win->y + i, x - 1, "  ");
	}
	i = 0;
	while (++i < x)
	{
		mvprintw(win->y, i, " ");
		mvprintw(y, i, " ");
	}
}

void	draw_tile(t_game *g, t_tile *tile)
{
	int		x;
	int		y;
	char	*buff;

	attron(COLOR_PAIR(3));
	y = 0;
	while (++y < g->tile_height)
	{
		x = 0;
		while (++x < g->tile_width)
			mvprintw(tile->y + y, tile->x + x, " ");
	}
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	attron(COLOR_PAIR(4));
	if (tile->value > 0)
	{
		buff = ft_itoa(tile->value);
		mvprintw(tile->y + g->tile_height / 2,
			tile->x + g->tile_width / 2 - (ft_nbrlen(tile->value) / 2),
			buff);
		if (buff)
			free(buff);
	}
	attroff(COLOR_PAIR(4));
}

void	draw_board(t_game *g)
{
	int		x;
	int		y;

	init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
	y = -1;
	while (g->tiles[++y])
	{
		x = -1;
		while (g->tiles[y][++x])
			draw_tile(g, g->tiles[y][x]);
	}
	attroff(COLOR_PAIR(3));
}

void	maj_gps(t_game *g)
{
	int		x;
	int		y;

	y = -1;
	while (++y < g->tile_size)
	{
		x = -1;
		while (++x < g->tile_size)
		{
			g->tiles[y][x]->x = (x * g->tile_width) + 3;
			g->tiles[y][x]->y = (y * g->tile_height) + 1;
		}
	}
}

void	board_create(t_game *g)
{
	int		x;
	int		y;
	t_tile	***tiles;

	if (!(tiles = (t_tile ***)ft_memalloc(sizeof(t_tile **) * g->tile_size + 1)))
		return ;
	y = -1;
	while (++y < g->tile_size)
	{
		if (!(tiles[y] = (t_tile **)ft_memalloc(sizeof(t_tile *) * g->tile_size + 1)))
			return ;
		x = -1;
		while (++x < g->tile_size)
		{
			if (!(tiles[y][x] = (t_tile *)ft_memalloc(sizeof(t_tile))))
				return ;
			tiles[y][x]->x = (x * g->tile_width) + 3;
			tiles[y][x]->y = (y * g->tile_height) + 1;
		}
	}
	tiles[0][2]->value = 2;
	tiles[2][0]->value = 2;
	g->tiles = tiles;
	draw_board(g);
}

void	background(t_game *g)
{
	init_pair(1, COLOR_BLACK, COLOR_CYAN);
	init_pair(2, COLOR_WHITE, COLOR_WHITE);

	attron(COLOR_PAIR(2));
	borders(&g->board);
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(1));
	mvprintw(g->board.y, g->board.x + 2, " Board game ");
	attroff(COLOR_PAIR(1));

	attron(COLOR_PAIR(2));
	borders(&g->score);
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(1));
	mvprintw(g->score.y, g->score.x + 2, " Score ");
	attroff(COLOR_PAIR(1));
}

void	redraw(t_game *g)
{
	game_windows(g);
	maj_gps(g);
	wclear(stdscr);
	background(g);
	draw_board(g);
}

void	resize(t_game *g)
{
	int	new_w;
	int	new_h;

	getmaxyx(stdscr, new_h, new_w);
	if (new_w != g->w || new_h != g->h)
	{
		g->w = new_w;
		g->h = new_h;
		redraw(g);
	}
	refresh();
}