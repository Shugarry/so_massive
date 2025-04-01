/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:57:16 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/01 12:22:34 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
}

void	free_exit(t_game *game, char *error_msg, int status)
{
	ft_printf("Error");
	if (error_msg)
		ft_printf(": %s", error_msg);
	ft_printf("\n");
	free_map(game);
	exit(status);
}
