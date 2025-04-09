/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:24:41 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/01 20:41:45 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	parse_map(t_game *game, int fd)
{
	char	*line;
	int		i;

	game->map = (char **)malloc((game->height + 1) * sizeof(char *));
	if (!game->map)
		free_exit(game, "malloc fail", EXIT_FAILURE);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		game->map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	game->map[i] = NULL;
	game->width = ft_strlen(game->map[0]);
	close(fd);
}

bool	is_file_valid(t_game *game, const char *file, int *fd)
{
	char	*dot;
	bool	valid;
	char	*line;

	valid = false;
	*fd = open(file, O_RDONLY);
	dot = ft_strrchr(file, '.');
	if (*fd != -1)
		valid = (dot && ft_strncmp(dot, ".ber", 4) == 0);
	if (valid)
	{
		line = get_next_line(*fd);
		while (line)
		{
			game->height++;
			free(line);
			line = get_next_line(*fd);
		}
	}
	if (*fd != -1)
		close(*fd);
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
		valid = false;
	return (valid);
}

void	init_game(t_game *game)
{
	game->map = NULL;
	game->width = 0;
	game->height = 0;
	game->stats.start = false;
	game->stats.exit = false;
	game->stats.items = 0;
	game->stats.pos.x = 0;
	game->stats.pos.y = 0;
	game->mlx = NULL;
}
