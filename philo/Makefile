# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ride-sou <ride-sou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 15:06:43 by ride-sou          #+#    #+#              #
#    Updated: 2023/09/22 18:05:19 by ride-sou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philo_main.c philo_aux.c philo_init.c philo_actions.c philo_rules.c

OBJS = ${SRC:.c=.o}

RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -pthread -fsanitize=thread

# COLORS #

RESET = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m

# ------ #

all:	${NAME}

$(NAME): ${OBJS}
		cc ${CFLAGS} ${OBJS} -o ${NAME}
		echo "${BLUE}--- Compilation completed ---${RESET}"
		echo "${GREEN}--- ./philo has been created ---${RESET}"

clean:
		${RM} ${OBJS}
		echo "${YELLOW}--- Objects cleaned ---${RESET}"

fclean: clean
		${RM} ${NAME}
		echo "${RED}--- All cleaned ---${RESET}"

re: fclean all

.PHONY: all clean fclean re

.SILENT: