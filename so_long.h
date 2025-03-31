#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_game
{
	char	*map[30];
	int		length;
	int		height;
}	t_game;

typedef struct s_conditions
{
	int	start_pos;
	int	exit;
	int	collectible;
}	t_conditions;

// freeing
void	free_exit(t_game *game, char *error_msg);

#endif
