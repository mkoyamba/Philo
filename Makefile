# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 17:08:30 by mkoyamba          #+#    #+#              #
#    Updated: 2022/04/26 13:41:33 by mkoyamba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

NAME = philo

INC_DIR =	.

SRC =	main.c \

BONUS =	

OBJ = $(SRC:.c=.o)

OBJB = $(BONUS:bonus.c=bonus.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $(OBJ) -o $(NAME)

%bonus.o: %bonus.c
	@gcc $(CFLAGS) -I $(INC_DIR) -c $< -o $@
	
%.o: %.c
	@gcc $(CFLAGS) -I $(INC_DIR) -c $< -o $@


bonus: $(OBJB)
	@gcc $(CFLAGS) $(OBJB) -o $(NAME)

clean:
	@rm -rf $(OBJ) $(OBJB)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, bonus, re