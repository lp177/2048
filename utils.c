/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <llaffile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 18:02:55 by llaffile          #+#    #+#             */
/*   Updated: 2015/02/28 20:49:04 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"


void			*reverse(void *tab, size_t max, size_t size)
{
	char	*reverse_tab;
	int		i;

	if ((reverse_tab = (char *)ft_memalloc(max * size)) == NULL)
		return (NULL);
	i = 0;
	while (i < max)
	{
		ft_memcpy(reverse_tab + (i * size), tab + ((max - i - 1) * size), size);
		i++;
	}
	free(tab);
	return (reverse_tab);
}

void			**tabAlloc(size_t x, size_t y, size_t size)
{
	char	**tab;
	int		i;

	if ((tab = (char **)ft_memalloc(x * sizeof(void *))) == NULL)
		return (NULL);
	i = 0;
	while (i < x)
	{
		if ((tab[i] = (char *)ft_memalloc(y * size)) == NULL)
			return (NULL);
		i++;
	}
	return ((void **)tab);
}

void			tabFree(void **tab, size_t size)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = (char **)tab
	while (i < size)
	{
		free(ptr[i]);
		i++;
	}
	free (tab);
	return ;
}
