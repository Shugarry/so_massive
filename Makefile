# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 11:57:09 by frey-gal          #+#    #+#              #
#    Updated: 2025/04/10 01:39:49 by frey-gal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPILE = cc -Wall -Wextra -Werror -fsanitize=address # -g

NAME = so_long

SRC = \
srcs/so_long.c \
srcs/error.c \
srcs/parsing.c \
srcs/validation.c \
srcs/hook.c

OBJ = $(SRC:.c=.o)

#==================================MINILIBX====================================#

MLX42_DIR = ./MLX42

MLX42 = build/libmlx42.a

MLXFLAGS = -I ./MLX42/include -ldl -lglfw -pthread -lm

#==================================MINILIBX====================================#


#=======================TO MAKE SURE MAKEFILE RECOMPILES=======================#

# LIBFT files dependencies
LIB_DEP = \
libft/ft_atoi.c \
libft/ft_bzero.c \
libft/ft_calloc.c \
libft/ft_isalnum.c \
libft/ft_isalpha.c \
libft/ft_isascii.c \
libft/ft_isdigit.c \
libft/ft_isprint.c \
libft/ft_itoa.c \
libft/ft_memchr.c \
libft/ft_memcmp.c \
libft/ft_memcpy.c \
libft/ft_memmove.c \
libft/ft_memset.c \
libft/ft_putchar_fd.c \
libft/ft_putendl_fd.c \
libft/ft_putnbr_fd.c \
libft/ft_putstr_fd.c \
libft/ft_split.c \
libft/ft_strchr.c \
libft/ft_strdup.c \
libft/ft_striteri.c \
libft/ft_strjoin.c \
libft/ft_strlcat.c \
libft/ft_strlcpy.c \
libft/ft_strlen.c \
libft/ft_strmapi.c \
libft/ft_strncmp.c \
libft/ft_strnstr.c \
libft/ft_strrchr.c \
libft/ft_strtrim.c \
libft/ft_substr.c \
libft/ft_tolower.c \
libft/ft_toupper.c \
libft/ft_printf.c \
libft/print_base.c \
libft/print_uns.c \
libft/print_ptr.c \
libft/print_str.c \
libft/print_char.c \
libft/get_next_line.c \
libft/ft_lstnew_bonus.c \
libft/ft_lstadd_front_bonus.c \
libft/ft_lstsize_bonus.c \
libft/ft_lstlast_bonus.c \
libft/ft_lstadd_back_bonus.c \
libft/ft_lstdelone_bonus.c \
libft/ft_lstclear_bonus.c \
libft/ft_lstiter_bonus.c \
libft/ft_lstmap_bonus.c \
libft/get_next_line_bonus.c \
libft/get_next_line_utils_bonus.c \
libft/get_next_line_utils.c \
libft/libft.h \
libft/get_next_line.h \
libft/get_next_line_bonus.h \
libft/ft_printf.h \

OBJ_DEP = $(LIB_DEP:.c=.o) #Dependencies for the objects

ALL_DEP = Makefile so_long.h $(OBJ) $(LIB_DEP) $(OBJ_DEP) libft/Makefile \
		 
#=======================TO MAKE SURE MAKEFILE RECOMPILES=======================#

all: $(NAME)

$(NAME): $(ALL_DEP) $(MLX42)
	@make all -C libft
	@$(COMPILE) $(SRC) ./libft/libft.a $(MLX42) $(MLXFLAGS) -o $(NAME)

$(MLX42):
	@cmake $(MLX42_DIR) -B build
	@cmake --build build -j4

clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@rm -rf build
	@echo 'all clean!! :)'

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
