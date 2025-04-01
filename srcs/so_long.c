/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:56:44 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/01 20:50:51 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	create_check_map(t_game *game, int *fd)
{
	char	**cpy;
	int		i;

	i = 0;
	parse_map(game, *fd);
	check_borders(game);
	check_dimensions(game);
	check_map(game);
	cpy = copy_map(game);
	flood(game->stats.start_pos[0], game->stats.start_pos[1], cpy);
	while (cpy[i])
	{
		free(cpy[i]);
		i++;
	}
	free(cpy);
	for (int i = 0; i < game->height; i++)
		printf("%s          %d\n", game->map[i], i);
}
/*
static void	hook(void *param)
{
	t_game	*game;
	
	game = param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		free_exit(game, "Exited succesfully", EXIT_SUCCESS);
	}
	
}

void	run(t_game *game)
{
	game->mlx = mlx_init(400, 400, "so_long", false); // initialize window 
	if (!game->mlx)
		free_exit(game, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE); // the malloc can fail
	mlx_loop_hook(game->mlx, hook, game); // kind of like attach your own function to the loop
	mlx_loop(game->mlx); // main window loop

	free_exit(game, NULL, EXIT_SUCCESS);
}

*/
int main(int ac, char **av)
{
	int		fd;
	t_game	game;

	init_game(&game);
	if (ac != 2 || !is_file_valid(av[1], &fd))
		free_exit(&game, "Usage: ./so_long <mapfile.ber>", EXIT_FAILURE);
	create_check_map(&game, &fd);
//	run(&game);
	free_exit(&game, NULL, EXIT_SUCCESS);
}
