SRCDIR        =     srcs/mandatory/
SRC           =		pipex.c                 \
                	init.c                  \
                	ft_split.c              \
                	get_cmd_path.c          \
                	path_parsing_utils.c    \
                	ft_free.c               \
                	error_handler.c         \


B_SRCDIR    =		srcs/bonus/
B_SRC		=		pipex.c					\
                	process_exec.c			\
 					close_fd.c				\
 					ft_split.c				\
 					get_cmd_path.c			\
 					get_cmd_path_utils.c	\
 					utils.c					\
					ft_free.c				\
					ft_free_2.c				\
					error_handler.c			\
					get_next_line.c			\
					init.c					\


OBJDIR        =     obj/
OBJ            =     $(addprefix $(OBJDIR), $(SRC:.c=.o))

B_OBJDIR	=		$(OBJDIR)/bonus
B_OBJ		=		$(addprefix $(B_OBJDIR), $(B_SRC:.c=.o))

NAME		=		pipex
B_NAME		=		pipex_bonus

CC			=		cc
RM			=		rm -f
CFLAGS		=		-Wall -Wextra -Werror -g

$(OBJDIR)%.o:		$(SRCDIR)%.c
					@mkdir -p $(OBJDIR)
					$(CC) -I ./includes $(CFLAGS) -c $< -o $@

$(B_OBJDIR)%.o:		$(B_SRCDIR)%.c
					@mkdir -p $(B_OBJDIR)
					$(CC) -I ./includes $(CFLAGS) -c $< -o $@

$(NAME):			$(OBJ)
						@$(CC) -g $^ -o $@

$(B_NAME):			$(B_OBJ)
						@$(CC) -g $^ -o $@

all:				$(NAME) $(B_NAME)

bonus:				$(B_NAME)

clean:
					$(RM) -r $(OBJDIR)
#					$(RM) -r $(B_OBJDIR)

fclean:				clean
					$(RM) $(NAME)
					$(RM) $(B_NAME)

re:					fclean all

.PHONY:				all bonus clean fclean re
