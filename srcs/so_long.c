#include "../so_long.h"

void	parse_map(t_game *game, int fd)
{
	int i;

	i = 0;
	game->map[i] = get_next_line(fd);
	game->length = ft_strlen(game->map[i]);
	while (game->map[i])
	{
		i++;
		game->map[i] = get_next_line(fd);
	}
	game->height = i;
}

bool	check_dimensions(t_game *game)
{
	int	i;

	i = 0;
	if (game->height < 4 || game->length < 4) 
		free_exit(game, "Incorrect dimensions");
	while (game->map[i])
	{
		if (game->length != ft_strlen(game->map[i]))
			free_exit(game, "Incorrect dimensions");
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
	if (*fd == -1)
		valid = (dot && ft_strncmp(dot, ".ber", 4) == 0);
	return (valid);
}


void	check_borders(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] != '1' && ((i == game->length - 1)
				|| (i == 0) || (j == game->height - 1) || (j == 0)))
				free_exit(game, "Walls don't cover map");
			j++;
		}
		i++;
	}
}

void	check_map(t_game *game)
{
	int	i;
	int	j;
	t_conditions	conditions;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] != '0' || game->map[i][j] != '1')
				;
			else if (game->map[i][j] == 'C')
				conditions;
			else if (game->map[i][j] == 'E')
					;
			else if (game->map[i][j] == 'P')
				;
			else
				free_exit(game, "Map is invalid");
			j++;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	t_game game;
	int	fd;

	if (ac != 2 || !is_file_valid(av[1], &fd))
	{
		printf("Invalid map format. Usage: %s <mapfile.ber>\n", av[0]);
		return (1);
	}
	parse_map(&game, fd);
	check_map(&game);
	close(fd);
}
