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

static void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	size_t	copy_size;
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}

void	parse_map(t_game *game, int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		game->map = ft_realloc(game->map, i * PP_CHAR, (i + 1) * PP_CHAR);
		if (game->map == NULL)
			free_exit(game, "malloc failure", EXIT_FAILURE);
		game->map[i] = ft_strtrim(tmp, "\n");
		free(tmp);
		if (game->map[i] == NULL)
			free_exit(game, "malloc failure", EXIT_FAILURE);
		i++;
		tmp = get_next_line(fd);
	}
	game->map[i] = NULL;
	game->height = i;
	game->length = ft_strlen(game->map[0]);
	close(fd);
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

void	init_game(t_game *game)
{
	int	i;

	game->map = NULL;
	game->length = 0;
	game->height = 0;
	game->stats.start = false;
	game->stats.exit = false;
	game->stats.items = 0;
	game->stats.start_pos[0] = 0;
	game->stats.start_pos[1] = 0;
	game->mlx = NULL;
}
