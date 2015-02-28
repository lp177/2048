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

#include <ncurses.h>

#include "libft.h"

typedef struct		s_game
{
	int		score_size;
	int		x;
	int		y;
	WINDOW	*field;
	WINDOW	*score;
	WINDOW	*home;
}					t_game;

#endif
