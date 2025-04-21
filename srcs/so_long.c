/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:56:44 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/10 02:30:23 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	create_check_map(t_game *game, int *fd)
{
	char	**cpy;
	int		i;
	bool	valid;

	i = -1;
	valid = true;
	parse_map(game, *fd);
	check_dimensions(game);
	check_borders(game);
	check_map(game);
	if (!game->stats.start || !game->stats.exit || !game->stats.items)
		free_exit(game, "Invalid components", EXIT_FAILURE);
	cpy = copy_map(game);
	flood(game->stats.pos.y, game->stats.pos.x, cpy);
	while (++i < game->height)
	{
		if (ft_strchr(cpy[i], 'E') || ft_strchr(cpy[i], 'C')
			|| ft_strchr(cpy[i], 'P'))
			valid = false;
		free(cpy[i]);
	}
	free(cpy);
	if (!valid)
		free_exit(game, "Unsolvable map or invalid chars", EXIT_FAILURE);
}

void	draw_map(t_game *game, t_textures *rsrcs)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			mlx_image_to_window(game->mlx, rsrcs->floor, PS * j, PS * i);
			if (game->map[i][j] == '1')
				mlx_image_to_window(game->mlx, rsrcs->wall, PS * j, PS * i);
			if (game->map[i][j] == 'C')
				mlx_image_to_window(game->mlx, rsrcs->item, PS * j, PS * i);
			if (game->map[i][j] == 'E')
			{
				game->stats.exit_p.x = j;
				game->stats.exit_p.y = i;
			}
		}
	}
	mlx_image_to_window(game->mlx, rsrcs->player, \
					PS * game->stats.pos.x, PS * game->stats.pos.y);
	mlx_image_to_window(game->mlx, rsrcs->exit_a, \
					PS * game->stats.exit_p.x, PS * game->stats.exit_p.y);
}

t_textures	init_resources(t_game *game)
{
	t_textures	resources;

	resources.wall = add_image(game->mlx, "textures/wall.png", PS, PS);
	if (resources.wall == NULL)
		free_exit(game, "Texture failure", EXIT_FAILURE);
	resources.floor = add_image(game->mlx, "textures/floor.png", PS, PS);
	if (resources.floor == NULL)
		free_exit(game, "Texture failure", EXIT_FAILURE);
	resources.item = add_image(game->mlx, "textures/item.png", PS, PS);
	if (resources.item == NULL)
		free_exit(game, "Texture failure", EXIT_FAILURE);
	resources.player = add_image(game->mlx, "textures/player.png", PS, PS);
	if (resources.player == NULL)
		free_exit(game, "Texture failure", EXIT_FAILURE);
	resources.exit_a = add_image(game->mlx, "textures/exit_a.png", PS, PS);
	if (resources.exit_a == NULL)
		free_exit(game, "Texture failure", EXIT_FAILURE);
	resources.exit_b = add_image(game->mlx, "textures/exit_b.png", PS, PS);
	if (resources.exit_b == NULL)
		free_exit(game, "Texture failure", EXIT_FAILURE);
	return (resources);
}

void	run(t_game *game)
{
	game->mlx = mlx_init(PS * game->width, PS * game->height, "so_long", false);
	if (!game->mlx)
		free_exit(game, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	game->resources = init_resources(game);
	draw_map(game, &game->resources);
	mlx_key_hook(game->mlx, &keys, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	int		fd;
	t_game	game;

	init_game(&game);
	if (ac != 2 || !is_file_valid(&game, av[1], &fd))
	{
		free_exit(&game,
			"Invalid or empty file. Usage: ./so_long <mapfile.ber>",
			EXIT_FAILURE);
	}
	create_check_map(&game, &fd);
	run(&game);
	free_exit(&game, "MLX exited succesfully!", EXIT_SUCCESS);
}
