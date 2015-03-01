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

t_game *g;

void	game_io(void)
{
	char			c;

	while ((c = wgetch(g->home)) != ERR)
	{
		waddch(g->board, c);
		wrefresh(g->board);
		wrefresh(g->score);
	}
}

void	game_windows(void)
{
	g->score_size = 10;
	getmaxyx(stdscr, g->y, g->x);
	g->home = newwin(g->y, g->x, 0, 0);
	g->board = newwin(g->y - g->score_size, g->x, 0, 0);
	g->score = newwin(g->score_size, g->x, g->y - g->score_size, 0);
}

void	listen(void)
{
	char	c;

	c = 0;
	while (c != 27)
	{
		resize();
		c = wgetch(g->home);
	}
}

void	game(void)
{
	game_windows();
	background();
	refresh_w();
	listen();
	delwin(g->board);
	delwin(g->score);
}

int main(void)
{
	if (!(g = (t_game *)ft_memalloc(sizeof(t_game))))
		return (-1);
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	game();
	endwin();
	return (0);
}
