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
SRCS 			= philo_one.c \
					utils/ft_atoi.c \
					utils/ft_isdigit.c \

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
