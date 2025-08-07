# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/28 12:56:25 by krepo             #+#    #+#              #
#    Updated: 2025/08/07 15:36:00 by krepo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= fdf

SRC_DIR		:= srcs
OBJ_DIR		:= objs
INC_DIR		:= include

SRCS		:= calculate.c draw.c draw_line.c fdf.c hooks.c manipulate_view.c \
			   memory.c parse.c parse_utils.c rotate.c fdf_utils.c

HEADER		:= fdf.h

OBJS		:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g

RM			:= rm -f

LIBFT_DIR	:= ./libft
LIBFT		:= $(LIBFT_DIR)/libft.a
LIBFT_H		:= $(LIBFT_DIR)/libft.h

MLX_DIR		:= ./mlx
MLX			:= $(MLX_DIR)/libmlx.a
MLX_H		:= $(MLX_DIR)/mlx.h

INC			:= -I./$(INC_DIR)
LIBS		:= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

$(NAME): $(OBJS) $(LIBFT) $(MLX)
		$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/$(HEADER) $(LIBFT_H) $(MLX_H) | $(OBJ_DIR)
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

$(MLX):
		$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

.SECONDARY: $(OBJS)

all: $(NAME)

clean:
		$(RM) -r $(OBJ_DIR)
		$(MAKE) -C $(LIBFT_DIR) clean
		$(MAKE) -C $(MLX_DIR) clean

fclean: clean
		$(RM) $(NAME)
		$(MAKE) -C $(LIBFT_DIR) fclean
		$(MAKE) -C $MLX_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
