# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/22 17:52:51 by diolivei          #+#    #+#              #
#    Updated: 2025/05/23 16:15:38 by diolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

CC = cc -g

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell

SRCS = $(shell find src -type f -name "*.c")

LIBFT = ./libraries/libft.a

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

clean:
	rm -rf $(OBJS)
	@echo "$(YELLOW)Removing $(NAME) and libraries objects files$(RESET)"
	@if [ -d libraries ]; then \
		cd libraries && make clean; \
	fi

fclean: clean
	rm -rf $(NAME)
	@echo "$(RED)Removing $(NAME) executable$(RESET)"
	@if [ -d libraries ]; then \
		cd libraries && make fclean; \
	fi

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --leak-check=full ./minishell

$(LIBFT):
	cd libraries && make

.PHONY: all clean fclean re
