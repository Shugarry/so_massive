/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:56:44 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/07 19:33:28 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void p_map(t_game *game)
{
	for (int i = 0; i < game->height; i++)
			printf("%s\n", game->map[i]);
}

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
		;
	*/
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		free_exit(game, "Finished succesfully", EXIT_SUCCESS);
}

void	draw_map(t_game *game, t_textures *resources)
{
	int	i;
	int	j;


	i = 0;
	while (i < game->height)
	{
		j = 0;
		printf("%s\n", game->map[i]);
		while (j < game->width)
		{
			mlx_image_to_window(game->mlx, resources->floor, PIXEL_SIZE * j, PIXEL_SIZE * i);
			if (game->map[i][j] == '1')
				mlx_image_to_window(game->mlx, resources->wall, PIXEL_SIZE * j, PIXEL_SIZE * i);
			if (game->map[i][j] == 'C')
				mlx_image_to_window(game->mlx, resources->item, PIXEL_SIZE * j, PIXEL_SIZE * i);
			j++;
		}
		i++;
	}
}

mlx_image_t	*add_image(mlx_t *mlx, const char *path, uint32_t width, uint32_t height)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		return (NULL);
	if (!mlx_resize_image(image, width, height))
		return (NULL);
	return (image);
}

void	init_resources(t_game *game, t_textures *resources)
{
	resources->wall = add_image(game->mlx, "textures/wall.png", PIXEL_SIZE, PIXEL_SIZE);
	resources->floor = add_image(game->mlx, "textures/floor.png", PIXEL_SIZE, PIXEL_SIZE);
	resources->item = add_image(game->mlx, "textures/item.png", PIXEL_SIZE, PIXEL_SIZE);
	// resources->player = load_resized_image(game->mlx, "textures/player.png", 50, 50);
}

void	run(t_game *game)
{
	t_textures	resources;

	game->mlx = mlx_init(PIXEL_SIZE * game->width, PIXEL_SIZE * game->height, "so_long", false);
	if (!game->mlx)
		free_exit(game, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE); // the malloc can fail
	init_resources(game, &resources);
	draw_map(game, &resources);
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
