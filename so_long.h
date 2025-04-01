/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:57:00 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/01 12:27:41 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>


typedef struct s_stats
{
	bool	start;
	bool	exit;
	int		items;
	int		start_pos[2];
}	t_stats;

typedef struct s_game
{
	char			*map[30];
	int				length;
	int				height;
	t_stats			stats;
}	t_game;

// freeing
void	free_exit(t_game *game, char *error_msg, int status);

#endif
