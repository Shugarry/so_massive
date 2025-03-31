#include "../so_long.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
}

void	free_exit(t_game *game, char *error_msg)
{
	ft_printf("Error");
	if (error_msg)
		ft_printf(": %s", error_msg);
	ft_printf("\n");
	free_map(game);
}
