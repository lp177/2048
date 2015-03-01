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

typedef struct		s_game
{
	int			score_size;
	int			x;
	int			y;
	WINDOW		*board;
	WINDOW		*score;
	WINDOW		*home;
}					t_game;

extern t_game		*g;
			
void			borders(WINDOW *screen);
void			background(void);
void			refresh_w(void);
void			resize(void);

#endif
