/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2048.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luperez <luperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 00:22:43 by luperez           #+#    #+#             */
/*   Updated: 2015/02/28 04:54:05 by luperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_2048_H
# define GAME_2048_h

#include <signal.h>
#include <ncurses.h>

#include "libft/includes/libft.h"

typedef struct		s_window
{
	int			x;
	int			y;
	int			w;
	int			h;
}					t_window;

typedef struct		s_tile
{
	int				value;
	int				x;
	int				y;
}					t_tile;

typedef struct		s_game
{
	int			score_size;
	int			tile_size;
	int			tile_width;
	int			tile_height;
	int			w;
	int			h;
	t_tile		***tiles;
	t_window	board;
	t_window	score;
}					t_game;

enum e_const
{
	WIN_VALUE = 2048
};

# define TILE_SIZE 4

void			game_windows(t_game *g);
void			board_create(t_game *g);

void			redraw(t_game *g);
void			borders(t_window *win);
void			background(t_game *g);
void			resize(t_game *g);
void			maj_gps(t_game *g);

void			displacement(t_game *g, int c);

#endif
