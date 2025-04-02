/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:57:16 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/02 18:43:26 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map && i < game->height)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

void	free_exit(t_game *game, char *error_msg, int status)
{
	if (game->mlx)
		mlx_terminate(game->mlx);
	free_map(game);
	if (status == EXIT_FAILURE)
		ft_printf("Error: ");
	if (error_msg)
		ft_printf("%s\n", error_msg);
	exit(status);
}
