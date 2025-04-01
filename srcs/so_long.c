/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:56:44 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/01 13:51:05 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	parse_map(t_game *game, int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = get_next_line(fd);
	game->map[i] = ft_strtrim(tmp, "\n");
	free(tmp);
	game->length = ft_strlen(game->map[i]);
	while (game->map[i])
	{
		i++;
		tmp = get_next_line(fd);
		game->map[i] = ft_strtrim(tmp, "\n");
		free(tmp);
	}
	game->height = i;
	close(fd);
}

bool	check_dimensions(t_game *game)
{
	int	i;

	i = 0;
	if (game->height < 3 || game->length < 3) 
		free_exit(game, "Incorrect dimensions", EXIT_FAILURE);
	while (game->map[i])
	{
		if (game->length != (int)ft_strlen(game->map[i]))
			free_exit(game, "Incorrect dimensions", EXIT_FAILURE);
		i++;
	}
	return (true);
}

bool	is_file_valid(const char *file, int *fd)
{
	char	*dot;
	bool	valid;

	*fd = open(file, O_RDONLY);
	dot = ft_strrchr(file, '.');
	if (*fd != -1)
		valid = (dot && ft_strncmp(dot, ".ber", 4) == 0);
	return (valid);
}


void	check_borders(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height - 1)
	{
		j = 0;
		while (j < game->length - 1)
		{
			if (game->map[i][j] != '1' && ((i == game->height - 1)
				|| (i == 0) || (j == game->length - 1) || (j == 0)))
				free_exit(game, "Walls don't cover map", EXIT_FAILURE);
			j++;
		}
		i++;
	}
}

void	check_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height - 1)
	{
		j = 0;
		while (j < game->length - 1)
		{
			if (game->map[i][j] == 'C')
			{
				game->stats.items += 1;
			}
			else if (game->map[i][j] == 'P' && game->stats.start == false)
			{
				game->stats.start = true;
				game->stats.start_pos[0] = i;
				game->stats.start_pos[1] = j;
			}
			else if (game->map[i][j] == 'E' && game->stats.exit == false)
				game->stats.exit = true;
			else if (game->map[i][j] != '0' && game->map[i][j] != '1')
				free_exit(game, "Map is invalid", EXIT_FAILURE);
			j++;
		}
		i++;
	}
}

t_game	copy_game(t_game game)
{
	t_game	tmp;
	int	i;

	i = -1;
	while (game.map[i++])
		tmp.map[i] = ft_strdup(game.map[i]);
	tmp.length = game.length;
	tmp.height = game.height;
	tmp.stats.start = game.stats.start;
	tmp.stats.exit = game.stats.exit;
	tmp.stats.items = game.stats.items;
	tmp.stats.start_pos[0] = game.stats.start_pos[0];
	tmp.stats.start_pos[1] = game.stats.start_pos[1];
	return (tmp);
}

void	flood(int i, int j, t_game *game)
{
	if (game->map[i][j] == '0' || game->map[i][j] == 'C'
		|| game->map[i][j] == 'E' || game->map[i][j] == 'P')
	{
		game->map[i][j] = 'X';
		flood(i + 1, j, game);
		flood(i - 1, j, game);
		flood(i, j + 1, game);
		flood(i, j - 1, game);
	}
}

void	init_game(t_game *game)
{
	int	i;

	i = -1;
	while (i++ < 30)
		game->map[i] = NULL;
	game->length = 0;
	game->height = 0;
	game->stats.start = false;
	game->stats.exit = false;
	game->stats.items = 0;
	game->stats.start_pos[0] = 0;
	game->stats.start_pos[1] = 0;
}

int main(int ac, char **av)
{
	t_game game;
	t_game cpy;
	int	fd;

	if (ac != 2 || !is_file_valid(av[1], &fd))
	{
		printf("Invalid map format. Usage: %s <mapfile.ber>\n", av[0]);
		return (1);
	}
	parse_map(&game, fd);
	check_borders(&game);
	check_dimensions(&game);
	check_map(&game);
	cpy = copy_game(game);
	flood(game.stats.start_pos[0], game.stats.start_pos[1], &cpy);
	for (int i = 0; cpy.map[i]; i++)
		printf("%s\n", cpy.map[i]);
	close(fd);
}
