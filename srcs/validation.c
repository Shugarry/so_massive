/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:26:02 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/10 01:29:46 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

bool	check_dimensions(t_game *game)
{
	int	i;

	i = 0;
	if (game->height < 3 || game->width < 3)
		free_exit(game, "Invalid dimensions", EXIT_FAILURE);
	while (game->map[i])
	{
		if (game->width != (int)ft_strlen(game->map[i]))
			free_exit(game, "Invalid dimensions", EXIT_FAILURE);
		i++;
	}
	return (true);
}

void	check_borders(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < game->width)
	{
		if (game->map[0][j] != '1' || game->map[game->height - 1][j] != '1')
			free_exit(game, "Walls don't cover map", EXIT_FAILURE);
		j++;
	}
	i = 0;
	while (i < game->height)
	{
		if (game->map[i][0] != '1' || game->map[i][game->width - 1] != '1')
			free_exit(game, "Walls don't cover map", EXIT_FAILURE);
		i++;
	}
}

void	check_map(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			if (game->map[i][j] == 'C')
				game->stats.items += 1;
			else if (game->map[i][j] == 'P' && game->stats.start == false)
			{
				game->stats.start = true;
				game->stats.pos.x = j;
				game->stats.pos.y = i;
				game->map[i][j] = '0';
			}
			else if (game->map[i][j] == 'E' && game->stats.exit == false)
				game->stats.exit = true;
			else if (game->map[i][j] != '0' && game->map[i][j] != '1')
				free_exit(game, "Invalid components", EXIT_FAILURE);
		}
	}
}

char	**copy_map(t_game *game)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!tmp)
		free_exit(game, "malloc failure", EXIT_FAILURE);
	while (i < game->height)
	{
		tmp[i] = ft_strdup(game->map[i]);
		if (!tmp[i])
		{
			i = 0;
			while (tmp[i])
				free(tmp[i++]);
			free(tmp);
			free_exit(game, "malloc failure", EXIT_FAILURE);
		}
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	flood(int i, int j, char **map)
{
	if (map[i][j] == '0' || map[i][j] == 'C'
		|| map[i][j] == 'E' || map[i][j] == 'P')
	{
		map[i][j] = 'X';
		flood(i + 1, j, map);
		flood(i - 1, j, map);
		flood(i, j + 1, map);
		flood(i, j - 1, map);
	}
}
