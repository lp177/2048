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

void	game_io(t_game *g)
{
	char	c;

	while ((c = wgetch(g->home)) != ERR)
	{
		waddch(g->field, c);
		wrefresh(g->field);
		wrefresh(g->score);
	}
}

void	game_windows(t_game *g)
{
	g->score_size = 10;
	getmaxyx(stdscr, g->y, g->x);
	g->home = newwin(g->y, g->x, 0, 0);
	g->field = newwin(g->y - g->score_size, g->x, 0, 0);
	g->score = newwin(g->score_size, g->x, g->y - g->score_size, 0);
}

void	background(t_game *g)
{
	wborder(g->field, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(g->field, 0, 0, "Field");
	mvwprintw(g->score, 0, 0, "Score");
	wborder(g->score, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(g->home);
	wrefresh(g->field);
	wrefresh(g->score);
}

void	game(void)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	game_windows(&game);
	background(&game);
	sleep(100);
	delwin(game.field);
	delwin(game.score);
}

int main(void)
{
	curs_set(FALSE);
	initscr();
	noecho();
	cbreak();
	game();
	endwin();
	return 0;
}
