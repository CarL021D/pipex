# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MakefileMandatory                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caboudar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 07:40:34 by caboudar          #+#    #+#              #
#    Updated: 2022/10/24 15:35:15 by caboudar         ###   ########.fr        #
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
C_DIR		= srcs/mandatory
C_DIR_B		= srcs/bonus/

C_FILES		=	pipex.c 				\
				init.c					\
				ft_split.c				\
				get_cmd_path.c			\
				path_parsing_utils.c	\
				ft_free.c				\
				error_handler.c			\

C_FILES_B	=	pipex.c					\
				process_exec.c			\
				ft_split.c				\
				get_cmd_path.c			\
				utils.c					\
				ft_free.c				\
				error_handler.c			\
				get_next_line.c			\
				get_next_line_utils.c	\
				init.c					\

SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))
SRCS_B		= $(patsubst %, $(C_DIR_B)/%, $(C_FILES_B))

# ################################## #
#               OBJECTS              #
# ################################## #
O_DIR		= objs

O_FILES		= $(C_FILES:.c=.o)
O_FILES_B	= $(C_FILES_B:.c=.o)

OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))
OBJS_B		= $(patsubst %, $(O_DIR)/%, $(O_FILES_B))

# ################################## #
#                FLAGS               #
# ################################## #
CFLAGS		= -Wall -Wextra -Werror -g

CINCLUDES	= -I ./includes \

# ################################## #
#                RULES               #
# ################################## #

all:		$(NAME)

$(NAME):	$(O_DIR) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $@
			@echo "${GREEN}- compiling pipex executable${RESET}"

bonus:		$(O_DIR) $(OBJS_B)
			@$(CC) $(CFLAGS) $(OBJS_B) -o $@
			@echo "${GREEN}- compiling bonus executable${RESET}"

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
