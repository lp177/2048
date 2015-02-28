/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2048.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <llaffile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 00:22:43 by luperez           #+#    #+#             */
/*   Updated: 2015/02/28 01:05:16 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_2048_H
# define GAME_2048_h

#include <curses.h>

#include "libft.h"

typedef struct	s_tile
{
	int			value;
}				t_tile;

typedef struct	s_env
{
	t_tile		grid[4][4];
	int			move;
	int			score;
}				t_env;

typedef enum	e_const
{
	WIN_VALUE = 2048
}				t_const;
#endif
