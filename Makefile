# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 02:23:03 by frey-gal          #+#    #+#              #
#    Updated: 2025/04/20 02:27:49 by frey-gal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================== VARS ==================================== #

NAME		= so_long
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address #-g

SRC			= srcs/so_long.c \
            srcs/error.c \
            srcs/parsing.c \
            srcs/validation.c \
            srcs/hook.c

OBJ			= $(SRC:.c=.o)

INCLUDES 	= -Ilibft -I./MLX42/include -I.

HDR			= so_long.h \

MLX42_DIR	= MLX42
MLX42		= build/libmlx42.a
MLXFLAGS	= -ldl -lglfw -pthread -lm

# ================================== LIBFT =================================== #

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

LIB_HDR		= \
libft/libft.h \
libft/get_next_line.h \
libft/get_next_line_bonus.h \
libft/ft_printf.h

LIB_SRC		= \
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

LIB_DEP = $(LIB_SRC) $(LIB_HDR) libft/Makefile 

# ================================== RULES =================================== #

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX42)
	@echo "\n==> Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42) $(MLXFLAGS) -o $(NAME)

srcs/%.o: srcs/%.c $(HDR) $(LIB_HDR) Makefile
	@echo " -> Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(LIB_DEP)
	@echo "\n==> Building Libft..."
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX42):
	@echo "\n==> Building MLX..."
	@cmake $(MLX42_DIR) -B build
	@cmake --build build -j4

clean:
	@echo "\n==> Cleaning project..."
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@rm -f $(OBJ)
	@rm -rf build

fclean: clean
	@echo "\n==> Full clean..."
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
