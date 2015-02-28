/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2048.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <llaffile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 00:22:43 by luperez           #+#    #+#             */
/*   Updated: 2015/02/28 23:28:11 by luperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_2048_H
# define GAME_2048_h

#include <curses.h>
#include <time.h>
#include "libft.h"

typedef struct		s_index
{
	int				x;
	int				y;
}					t_index;

typedef struct		s_tile
{
	int				value;
	int				x;
	int				y;
	int				merged;
	t_index			previous;
}					t_tile;

typedef struct		s_env
{
	t_tile			***grid;
	int				moved;
	int				score;
	int				won;
	int				over;
	int				keep_playing;
	int				start_tile;
	int				max_size;
}					t_env;


typedef struct		s_vector
{
	int				x;
	int				y;
}					t_vector;

typedef struct		s_target
{
	struct s_index	farthest;
	struct s_index	next;
}					t_target;

typedef enum		e_const
{
	WIN_VALUE = 2048
}					t_const;

typedef enum		e_direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
}					t_direction;

typedef enum		e_pos
{
	X,
	Y
}					t_pos;

void			moveTile(t_tile *tile, t_index cell, t_env env);
void			move_process(int direction, t_env *env);
void			foreachXY(t_env *env, t_vector vector);
void			mergeAndmove(t_env *env, t_index cell, t_tile *tile, t_vector vector);
t_tile			*addRandomTile(t_env env);
int				ismovesAvailable(t_env env);
int				istileMatchesAvailable(t_env env);
int				checkforMatches(t_env env, t_index pos, t_tile *tile);
void			prepareTiles(t_env env);
void			setup(t_env *env);
void			addStartTiles(t_env env);
void			keepPlaying(t_env *env);
int				isGameTerminated(t_env env);
int				positionsEqual(t_tile *tile, t_index pos);
int				**buildTraversals(t_vector vector, size_t max);
t_vector		getVector(int direction);
t_target		findFarthestPosition(t_index cell, t_vector vector, t_env env);
void			*reverse(void *tab, int max, size_t size);
void			**tabAlloc(size_t x, size_t y, size_t size);
void			tabFree(void **tab, size_t size);
int				iscellAvailable(t_index cell, t_env env);
int				iscellOccupied(t_index cell, t_env env);
t_tile			*getcellContent(t_index cell, t_env env);
int				iscellsAvailable(t_env env);
t_index			*getAvailablecells(t_env env, t_index *cells_a);
int				isWithinBounds(t_index pos, size_t max);
t_index			randomAvailableCell(t_env env);
t_tile			***new_Grid(t_env *env);
t_tile			***empty(size_t size);
void			insertTile(t_tile *tile, t_env env);
void			removeTile(t_tile *tile, t_env env);
void			clearEnv(t_env *env);
t_env			*new_Env(size_t size);
void 			updatePosition(t_tile *tile, t_index pos);
t_tile			*new_tile(t_index position, int value);
void			savePosition(t_tile *tile);


#endif
