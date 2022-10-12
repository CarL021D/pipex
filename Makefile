# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caboudar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 07:40:34 by caboudar          #+#    #+#              #
#    Updated: 2022/10/12 18:34:55 by caboudar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;91m
GREEN=\033[0;32m
RESET=\033[0m

# ################################## #
#               COMMAND              #
# ################################## #
CC			= gcc
MKDIR		= mkdir -p
RM			= rm -rf

# ################################## #
#              EXEC NAME             #
# ################################## #
NAME		= pipex

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= srcs
C_FILES		=	pipex.c \
				ft_split.c \
				path_parsing_utils.c \

SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))

# ################################## #
#               OBJECTS              #
# ################################## #
O_DIR		= objs
O_FILES		= $(C_FILES:.c=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))

# ################################## #
#                FLAGS               #
# ################################## #
CFLAGS		= -Wall -Wextra -Werror -g

CINCLUDES	= -I ./inc \

# ################################## #
#                RULES               #
# ################################## #

all:		$(NAME)

$(NAME):	$(O_DIR) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $@
			@echo "${GREEN}- compiling pipex executable${RESET}"

$(O_DIR)/%.o: $(C_DIR)/%.c
			@$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR):
			@$(MKDIR) $(O_DIR)
			@echo "${GREEN}- creating pipex objects directory${RESET}"

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			@$(RM) $(O_DIR)
			@echo "${RED}- deleting pipex objects${RESET}"

fclean:		clean
			@$(RM) $(NAME)
			@echo "${RED}- delete pipex executable${RESET}"

re:			fclean all

.PHONY: all check clean fclean re
