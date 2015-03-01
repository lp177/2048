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

	c = 0;
	while (c != 27)
	{
		resize(g);
		c = getch();
	}
}

void	game(t_game *g)
{
	game_windows(g);
	background(g);
	board_create(g);
	refresh();
	listen(g);
}

int main(void)
{
	t_game	*g;

	if (!(g = (t_game *)ft_memalloc(sizeof(t_game))))
		return (-1);
	g->tile_size = TILE_SIZE;
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	start_color();
	game(g);
	endwin();
	return (0);
}
