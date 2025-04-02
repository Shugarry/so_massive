/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:57:00 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/01 20:23:59 by frey-gal         ###   ########.fr       */
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
# define PP_CHAR sizeof(char**)


typedef struct s_stats
{
	bool	start;
	bool	exit;
	int		items;
	int		start_pos[2];
}	t_stats;

typedef struct s_game
{
	char			**map;
	mlx_t			*mlx;
	int				length;
	int				height;
	t_stats			stats;
}	t_game;

// error.c
void	free_exit(t_game *game, char *error_msg, int status);
void	free_map(t_game *game);
// parsing.c
void	parse_map(t_game *game, int fd);
bool	is_file_valid(t_game *game, const char *file, int *fd);
void	init_game(t_game *game);
// validation.c
bool	check_dimensions(t_game *game);
void	check_borders(t_game *game);
void	check_map(t_game *game);
char	**copy_map(t_game *game);
void	flood(int i, int j, char **map);

#endif
