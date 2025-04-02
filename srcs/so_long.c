/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:56:44 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/02 19:20:53 by frey-gal         ###   ########.fr       */
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
	while (i < game->height)
	{
		free(cpy[i]);
		i++;
	}
	free(cpy);
}

static void	keys(void *param)
{
	t_game	*game;

	game = param;
/*	
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(game->mlx, MLX_KEY_W))
		;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_A))
		;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(game->mlx, MLX_KEY_S))
		;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_D))
		;*/
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		free_exit(game, "Finished succesfully", EXIT_SUCCESS);
}

void	draw_map(t_game *game)
{
	mlx_texture_t	*tile;
	mlx_image_t		*img;

	tile = mlx_load_png("textures/square.png");
	img = mlx_texture_to_image(game->mlx, tile);
	mlx_delete_texture(tile);
	for (int i = 0; i < game->height; i++)
	{
		for (int j = 0; j < game->length; j++)
		{

		}
	}
	mlx_image_to_window(game->mlx, img, 0, 0);
}

void	run(t_game *game)
{
	game->mlx = mlx_init(game->length * 100, game->height * 100, "so_long", false); // initialize window
	if (!game->mlx)
		free_exit(game, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE); // the malloc can fail
	draw_map(game);
	mlx_loop_hook(game->mlx, keys, game);
	mlx_loop(game->mlx); // main window loop

}

int main(int ac, char **av)
{
	int		fd;
	t_game	game;

	init_game(&game);
	if (ac != 2 || !is_file_valid(&game, av[1], &fd))
		free_exit(&game, "Usage: ./so_long <mapfile.ber>", EXIT_FAILURE);
	create_check_map(&game, &fd);
	run(&game);
	free_exit(&game, "MLX crashed unexpectedly...", EXIT_FAILURE);
}
