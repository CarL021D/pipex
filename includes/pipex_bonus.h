/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:58:48 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/13 23:54:29 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/errno.h>

# define FD_IN 0
# define FD_OUT 1
# define BUFFER_SIZE 10

typedef struct s_cmd
{
	pid_t	*pid_arr;
	int		fd_in;
	int		fd_out;
	int		here_doc;
	int		**pipe_arr;
	int		pipe_here_doc[2];
	// int		pipe_[2];
	// int		temp_pipe[2];
	int		nb_cmd;
	int		arg_index;
	int		fork_count;
	char	*cmd_path;	
	char	**cmd_options;
	char	**envp;
}	t_cmd;

//                  PIPEX
char	*get_command_path(t_cmd *s_cmd, char *av);
void	exit_if_not_enough_args(int ac, char **av);
void	fd_in_init(t_cmd *s_cmd, char **av);
void	fd_out_init(t_cmd *s_cmd, int ac, char **av);
void	close_fds(t_cmd *s_cmd, int fd);
void	pipe_arr_init(t_cmd *s_cmd);
void	cmd_struct_init(t_cmd *s_cmd, int ac, char **av, char **envp);
void	set_here_doc(t_cmd *s_cmd, char **av);

//					PROCESS EXEC
void	fd_to_pipe_exec(t_cmd *s_cmd, char **av);
void	here_doc_to_pipe_exec(t_cmd *s_cmd, char **av);
void	pipe_to_pipe_exec(t_cmd *s_cmd, char **av);
void	pipe_to_fd_exec(t_cmd *s_cmd, char **av, int ac);

//                  UTILS
size_t	ft_strlen(char *str);
char	**ft_split(char *str, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*path_str(char *full_path);
char	*ft_strnstr(char *full_path, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);


//                  ERROR
void	exit_if_failed_dup(void);
void	exit_if_failed_fork(t_cmd *s_cmd);

//                  FREE
void	free_cmd_line(t_cmd *s_cmd);
void	free_double_tab(char **tab);
void	free_struct(t_cmd *s_cmd);
void	free_pipe_arr(t_cmd *s_cmd, int i);


//					GET NEXT LINE
char	*get_next_line(int fd);

#endif