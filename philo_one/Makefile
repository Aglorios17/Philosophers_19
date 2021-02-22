# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aglorios <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/20 13:33:12 by aglorios          #+#    #+#              #
#    Updated: 2020/03/11 14:39:59 by aglorios         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= philo_one
SRCS 			= main/philo_one.c \
					main/init.c \
					srcs/thread.c \
					srcs/get_values.c \
					srcs/do_things.c \
					utils/ft_atoi.c \
					utils/ft_isdigit.c \
					utils/ft_itoa.c \
					utils/ft_strdup.c \
					utils/ft_strlen.c \

OBJS			= ${SRCS:.c=.o}
INCLUDE 		= include/philo_one.h
CC				= gcc -Wall -Wextra -Werror -g  #-fsanitize=address
RM				= rm -f

all:			${NAME}
$(NAME):		${OBJS} 
				$(CC) -I./ $(OBJS) -o $@ -lpthread 
clean:
				${RM} ${OBJS}
fclean:			clean
				${RM} ${NAME}
re:				fclean all

.PHONY: all fclean clean re
