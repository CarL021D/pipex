/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:58:48 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/23 13:16:27 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/errno.h>

# define CHILD_1 1
# define CHILD_2 2
# define FD_IN 100
# define FD_OUT 101
# define MALLOC 102
# define PATH_ERROR 103

typedef struct s_cmd
{
	pid_t	pid_1;
	pid_t	pid_2;
	int		pipe_[2];
	int		fd_in;
	int		fd_out;
	char	*cmd_path;
	char	**cmd_options;
	char	**envp;
}	t_cmd;

//					PIPEX
char	*get_cmd_path(t_cmd *s_cmd, char *av);

//					INIT
void	init_cmd_struct(t_cmd *s_cmd, char **envp);
void	init_fd(int id, t_cmd *s_cmd, char **av);

//					UTILS
size_t	ft_strlen(char *str);
char	**ft_split(char *str, char c);

//					PATH PARSING
char	*path_str(char *full_path);
char	*ft_strnstr(char *full_path, const char *s2, size_t n);
char	*join_slash_and_comd_to_path(char *s1, char *s2);

//					ERROR
void	exit_if_not_5_args(int ac);
void	exit_if_failed_fd_open(t_cmd *s_cmd, int id);
void	exit_if_failed_dup(t_cmd *s_cmd);
void	exit_if_failed_fork(t_cmd *s_cmd, int child);
void	path_error(t_cmd *s_cmd, char *av, char **cmd, int id);

//					FREE
void	free_pp_arr(char **tab);
void	free_execve_params(t_cmd *s_cmd);

#endif
