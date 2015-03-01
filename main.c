/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luperez <luperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 23:57:31 by luperez           #+#    #+#             */
/*   Updated: 2015/02/28 05:00:10 by luperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	game_windows(t_game *g)
{
	getmaxyx(stdscr, g->h, g->w);
	g->tile_width = (g->w - 6) / g->tile_size;
	g->tile_height = (g->h - g->score_size - 10) / g->tile_size;
	g->score_size = 10;
	g->board.h = g->h - g->score_size + 1;
	g->board.w = g->w;
	g->score.h = g->score_size;
	g->score.w = g->w;
	g->score.y = g->board.h - 1;
}

void	listen(t_game *g)
{
	int		c;

ft_putstr("\n\n=====\nListen...\n====\n\n");
	c = getch();
	while (c == KEY_LEFT || c == KEY_RIGHT || c == KEY_UP || c == KEY_DOWN || c != 27)
	{
ft_putstr("\n\n=====\nWho?\n====\n\n");
		if (c == KEY_LEFT || c == KEY_RIGHT || c == KEY_UP || c == KEY_DOWN)
		{
			displacement(g, c);
			ft_putstr("\n\n====\nKey move detected\n====\n\n");
		}
		else
			ft_putstr("\n\n====\nNot a key for diplacement\n====\n\n");
		resize(g);
		c = getch();
	}
ft_putstr("\n\n=====\nEnd of listening...\n====\n\n");
}

void	game(t_game *g)
{
	game_windows(g);
	background(g);
	board_create(g);
	refresh();
	listen(g);
}

void	end_game(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (g->tiles[++y])
	{
		x = -1;
		while (g->tiles[y][++x])
			free(g->tiles[y][++x]);
	}
	free(g);
}

int main(void)
{
	t_game	*g;

	if (!(g = (t_game *)ft_memalloc(sizeof(t_game))))
		return (-1);
	g->tile_size = TILE_SIZE;
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	cbreak();
	curs_set(0);
	start_color();
	game(g);
	end_game(g);
	endwin();
	return (0);
}
