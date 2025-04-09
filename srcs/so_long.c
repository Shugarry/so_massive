/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:56:44 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/09 20:24:04 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	p_map(t_game *game)
{
	for (int i = 0; i < game->height; i++)
		printf("%s\n", game->map[i]);
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
	flood(game->stats.pos.y, game->stats.pos.x, cpy);
	while (i < game->height)
	{
		free(cpy[i]);
		i++;
	}
	free(cpy);
}

void	check_move(t_game *game, char tile, int x, int y)
{
	t_textures	rsrcs;
	t_pos		*pos;

	rsrcs = game->resources;
	pos = &game->stats.pos;
	pos->x += x;
	pos->y += y;
	if (tile == 'C')
	{
		mlx_image_to_window(game->mlx, rsrcs.floor, PS * pos->x, PS * pos->y);
		game->map[pos->y][pos->x] = '0';
		game->stats.items -= 1;
		if (game->stats.items == 0)
		{
			mlx_delete_image(game->mlx, rsrcs.exit_a);
		}
	}
	else if (tile == 'E' && game->stats.items != 0)
	{
		pos->x -= x;
		pos->y -= y;
		ft_printf("Get all items first!!!!");
	}
	else if (tile == 'E')
		free_exit(game, "You won!!!\n", EXIT_SUCCESS);
	rsrcs.player->instances[0].x += x * PS;
	rsrcs.player->instances[0].y += y * PS;
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
		ft_printf("womp womp can't move there");
	printf("tile: %c for W\n", game->map[pos->y][pos->x]);
	printf("tile: %c for A\n", game->map[pos->y][pos->x]);
	printf("tile: %c for S\n", game->map[pos->y][pos->x]);
	printf("tile: %c for D\n", game->map[pos->y][pos->x]);
	printf("---------------\n");
}


void keys(mlx_key_data_t keydata, void* param)
{
	t_game		*game;
	t_textures	resources;

	game = param;
	resources = game->resources;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		try_move(game, &game->stats.pos, 'W');
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		try_move(game, &game->stats.pos, 'A');
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		try_move(game, &game->stats.pos, 'S');
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		try_move(game, &game->stats.pos, 'D');
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		free_exit(game, "Finished succesfully", EXIT_SUCCESS);
}
/*
static (void *param)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(game->mlx, MLX_KEY_W))
		try_move(game, &game->stats.pos, 'W');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_A))
		try_move(game, &game->stats.pos, 'A');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(game->mlx, MLX_KEY_S))
		try_move(game, &game->stats.pos, 'S');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_D))
		try_move(game, &game->stats.pos, 'D');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		free_exit(game, "Finished succesfully", EXIT_SUCCESS);
}*/

void	draw_map(t_game *game, t_textures *rsrc)
{
	int	i;
	int	j;


	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			mlx_image_to_window(game->mlx, rsrc->floor, PS * j, PS * i);
			if (game->map[i][j] == '1')
				mlx_image_to_window(game->mlx, rsrc->wall, 	PS * j, PS * i);
			if (game->map[i][j] == 'C')
				mlx_image_to_window(game->mlx, rsrc->item, PS * j, PS * i);
			if (game->map[i][j] == 'E')
				mlx_image_to_window(game->mlx, rsrc->exit_a, PS * j, PS * i);
			j++;
		}
		i++;
	}
	mlx_image_to_window(game->mlx, rsrc->player, PS * game->stats.pos.x,
					 PS * game->stats.pos.y);
}

t_textures	init_resources(t_game *game)
{
	t_textures resources;

	resources.wall = add_image(game->mlx, "textures/wall.png", PS, PS);
	resources.floor = add_image(game->mlx, "textures/floor.png", PS, PS);
	resources.item = add_image(game->mlx, "textures/item.png", PS, PS);
	resources.player = add_image(game->mlx, "textures/player.png", PS, PS);
	resources.exit_a = add_image(game->mlx, "textures/exit_a.png", PS, PS);
	resources.exit_b = add_image(game->mlx, "textures/exit_b.png", PS, PS);
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
