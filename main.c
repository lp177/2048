/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luperez <luperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 23:57:31 by luperez           #+#    #+#             */
/*   Updated: 2015/02/28 00:37:06 by luperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include "game_2048.h"

void	game(void)
{

}

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	game();
	endwin();
	return (0);
}
