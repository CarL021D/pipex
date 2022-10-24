# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caboudar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 15:12:48 by caboudar          #+#    #+#              #
#    Updated: 2022/10/24 16:30:58 by caboudar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS	= 		srcs/pipex.c 				\
				srcs/ft_split.c				\
				srcs/get_cmd_path.c 		\
				srcs/path_parsing_utils.c	\
				srcs/ft_free.c				\
				srcs/error_handler.c		\
				
SRCS_B =		srcs/bonus/pipex.c					\
				srcs/bonus/ft_split.c				\
				srcs/bonus/get_cmd_path.c			\
				srcs/bonus/path_parsing_utils.c		\
				srcs/bonus/ft_free.c				\
				srcs/bonus/error_handler.c			\


OBJS	= ${SRCS:.c=.o}

OBJS_B	= ${SRCS_B:.c=.o}

CFLAGS	= -Wall -Werror -Wextra -g

CC		= gcc

RM		= rm -f

INCS    = includes

all:	${NAME}

.c.o:
		@$(CC) ${CFLAGS} -I$(INCS) -c $< -o $@

${NAME}:	${OBJS} ${MLX}
		@${CC} ${CFLAGS} ${OBJS} -lX11 -lXext -o pipex
		@printf "%s\e[0;32m pipex : Compiling object file into executable\n\e[0m" "-"

bonus: ${OBJS_B}
		${CC} ${CFLAGS} ${OBJS_B} -I$(INCS) -lX11 -lXext -o pipex
		@printf "%s\e[0;32m pipex : Compiling bonus object file into executable\n\e[0m" "-"

clean:
		@${RM} ${OBJS}
		@${RM} ${OBJS_B}
		@printf "%s\e[0;31m pipex : Delete all object files\n\e[0m" "-"

fclean:
		@${RM} ${OBJS}
		@${RM} ${OBJS_B}
		@printf "%s\e[0;31m pipex : Delete all object files\n\e[0m" "-"
		@${RM} ${NAME}
		@printf "%s\e[0;31m pipex : Delete executable\n\e[0m" "-"

re: fclean ${NAME}

.PHONY: all clean fclean re bonus