/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <llaffile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 18:04:16 by llaffile          #+#    #+#             */
/*   Updated: 2015/02/28 20:55:04 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void			insertTile(t_tile *tile, t_env env)
{
	env.grid[tile->x][tile->y] = tile;
	return ;
}

void			removeTile(t_tile *tile, t_env env)
{
	free(env.grid[tile->x][tile->y]);
	return ;
}

void			clearEnv(t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (i < env->max_size)
	{
		j = 0;
		while (j < env->max_size)
		{
			free(env->grid[i][j]);
			j++;
		}
		i++;
	}
	return ;
}

t_env			*new_Env(size_t size)
{
	t_env		*env;

	if ((env = ft_memalloc(sizeof(t_env))) == NULL)
		return (NULL);
	env->max_size = size;
	return (env);
}
