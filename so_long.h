#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>


typedef struct s_stats
{
	bool	start;
	bool	exit;
	int		items;
}	t_stats;

typedef struct s_game
{
	char			*map[30];
	int				length;
	int				height;
	t_stats			stats;
}	t_game;

// freeing
void	free_exit(t_game *game, char *error_msg);

#endif
