/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:57:00 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/10 02:01:59 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# define PS 30

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_stats
{
	bool	start;
	bool	exit;
	int		items;
	t_pos	pos;
	t_pos	exit_p;
	int		move_num;
}	t_stats;

typedef struct s_textures
{
	mlx_image_t		*wall;
	mlx_image_t		*floor;
	mlx_image_t		*item;
	mlx_image_t		*exit_a;
	mlx_image_t		*exit_b;
	mlx_image_t		*player;
}	t_textures;

typedef struct s_game
{
	char			**map;
	mlx_t			*mlx;
	int				width;
	int				height;
	t_stats			stats;
	t_textures		resources;
}	t_game;

// error.c
void		free_exit(t_game *game, char *error_msg, int status);
void		free_map(t_game *game);

// parsing.c
void		parse_map(t_game *game, int fd);
bool		is_file_valid(t_game *game, const char *file, int *fd);
void		init_game(t_game *game);

// validation.c
bool		check_dimensions(t_game *game);
void		check_borders(t_game *game);
void		check_map(t_game *game);
char		**copy_map(t_game *game);
void		flood(int i, int j, char **map);

// hooks.c
mlx_image_t	*add_image(mlx_t *mlx, const char *path, uint32_t w, uint32_t h);
void		check_move(t_game *game, char tile, int x, int y);
void		try_move(t_game *game, t_pos *pos, char dir);
void		keys(mlx_key_data_t keydata, void *param);

#endif
