/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 01:18:38 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/10 02:09:29 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

mlx_image_t	*add_image(mlx_t *mlx, const char *path, uint32_t w, uint32_t h)
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
	if (!mlx_resize_image(image, w, h))
		return (NULL);
	return (image);
}

static void	handle_item(t_game *game)
{
	t_textures	*rsrcs;
	t_pos		*pos;

	rsrcs = &game->resources;
	pos = &game->stats.pos;
	mlx_image_to_window(game->mlx, rsrcs->floor, PS * pos->x, PS * pos->y);
	game->map[pos->y][pos->x] = '0';
	game->stats.items -= 1;
	if (game->stats.items == 0)
	{
		mlx_delete_image(game->mlx, rsrcs->exit_a);
		mlx_image_to_window(game->mlx, rsrcs->exit_b, \
					PS * game->stats.exit_p.x, PS * game->stats.exit_p.y);
	}
}

void	check_move(t_game *game, char tile, int x, int y)
{
	t_textures	*rsrcs;
	t_pos		*pos;

	rsrcs = &game->resources;
	pos = &game->stats.pos;
	pos->x += x;
	pos->y += y;
	if (tile == 'C')
		handle_item(game);
	else if (tile == 'E' && game->stats.items != 0)
		ft_printf("Get all items first!!!\n");
	else if (tile == 'E')
		free_exit(game, "You won!!!\n", EXIT_SUCCESS);
	mlx_delete_image(game->mlx, rsrcs->player);
	rsrcs->player = add_image(game->mlx, "textures/player.png", PS, PS);
	mlx_image_to_window(game->mlx, rsrcs->player, PS * pos->x, PS * pos->y);
	game->stats.move_num += 1;
	ft_printf("You have moved %d, times\n", game->stats.move_num);
}

void	try_move(t_game *game, t_pos *pos, char dir)
{
	if (dir == 'W' && game->map[pos->y - 1][pos->x] != '1')
		check_move(game, game->map[pos->y - 1][pos->x], 0, -1);
	else if (dir == 'A' && game->map[pos->y][pos->x - 1] != '1')
		check_move(game, game->map[pos->y][pos->x - 1], -1, 0);
	else if (dir == 'S' && game->map[pos->y + 1][pos->x] != '1')
		check_move(game, game->map[pos->y + 1][pos->x], 0, 1);
	else if (dir == 'D' && game->map[pos->y][pos->x + 1] != '1')
		check_move(game, game->map[pos->y][pos->x + 1], 1, 0);
	else
		ft_printf("Can't move there!!!\n");
}

void	keys(mlx_key_data_t keydata, void *param)
{
	t_game		*game;

	game = param;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		try_move(game, &game->stats.pos, 'W');
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		try_move(game, &game->stats.pos, 'A');
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		try_move(game, &game->stats.pos, 'S');
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		try_move(game, &game->stats.pos, 'D');
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		free_exit(game, "MLX exited succesfully!", EXIT_SUCCESS);
}
