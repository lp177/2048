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
		waddch(g->field, c);
		wrefresh(g->field);
		wrefresh(g->score);
	}
}

void	game_windows(void)
{
	g->score_size = 10;
	getmaxyx(stdscr, g->y, g->x);
	g->home = newwin(g->y, g->x, 0, 0);
	g->field = newwin(g->y - g->score_size, g->x, 0, 0);
	g->score = newwin(g->score_size, g->x, g->y - g->score_size, 0);
}

void	borders(WINDOW *screen)
{
	int x, y, i;
	getmaxyx(screen, y, x);
	// 4 corners
	mvwprintw(screen, 0, 0, "+");
	mvwprintw(screen, y - 1, 0, "+");
	mvwprintw(screen, 0, x - 1, "+");
	mvwprintw(screen, y - 1, x - 1, "+");
	// sides
	for (i = 1; i < (y - 1); i++) {
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, x - 1, "|");
	}
	// top and bottom
	for (i = 1; i < (x - 1); i++) {
		mvwprintw(screen, 0, i, "-");
		mvwprintw(screen, y - 1, i, "-");
	}
}

void	background(void)
{
	borders(g->field);
	borders(g->score);
	mvwprintw(g->field, 1, 1, "Field");
	mvwprintw(g->score, 1, 1, "Score");
}

void	refresh_w(void)
{
	wrefresh(g->home);
	wrefresh(g->field);
	wrefresh(g->score);
}

void	resize(int placebo)
{
	int	new_y;
	int	new_x;

	(void)placebo;
	getmaxyx(stdscr, new_y, new_x);
	if (new_y != g->y || new_x != g->x)
	{
		g->x = new_x;
		g->y = new_y;
		wresize(g->field, new_y - g->score_size, new_x);
		wresize(g->score, g->score_size, new_x);
		mvwin(g->score, new_y - g->score_size, 0);
		wclear(stdscr);
		wclear(g->home);
		wclear(g->field);
		wclear(g->score);
		background();
	}
	refresh_w();
}

void	listen(void)
{
	char	c;

	//signal(SIGWINCH, resize);
	c = 0;
	while (c != 27)
	{
		resize(0);
		c = wgetch(g->home);
	}
}

void	game(void)
{
	game_windows();
	background();
	refresh_w();
	listen();
	delwin(g->field);
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
