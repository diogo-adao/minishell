# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppassos <ppassos@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/10 14:12:01 by ppassos           #+#    #+#              #
#    Updated: 2024/12/17 14:10:43 by ppassos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

CC = cc -g 

CFLAGS = -Wall -Wextra -Werror

#CFLAGS += -fsanitize=thread
#CFLAGS += -fsanitize=address 

NAME = minishell

SRCS = src/parsing/minishell.c src/parsing/ifbuiltins.c src/parsing/quotesutils.c

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