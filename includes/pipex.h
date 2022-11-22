/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:58:48 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/21 01:00:23 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/errno.h>

# define CHILD_1 1
# define CHILD_2 2
# define FD_IN 100
# define FD_OUT 101
# define MALLOC 102
# define NO_PATH 103

typedef struct s_cmd
{
	pid_t	pid_1;
	pid_t	pid_2;
	int		fd_in;
	int		fd_out;
	char	*cmd_path;
	char	*cmd2_path;
	char	**cmd_options;
	char	**cmd2_options;
}	t_cmd;

//					PIPEX
char	*get_command_path(t_cmd *s_cmd, char *av, char **envp);

//					INIT
void	init_cmd_struct(t_cmd *s_cmd);
void	init_fd_in_or_out(int id, t_cmd *s_cmd, char **av);

//					UTILS
size_t	ft_strlen(char *str);
char	**ft_split(char *str, char c);

//					PATH PARSING
char	*path_str(char *full_path);
char	*ft_strnstr(char *full_path, const char *s2, size_t n);

//					ERROR
void	exit_if_not_5_args(int ac);
void	exit_if_failed_fd_open(t_cmd *s_cmd, int id);
void	exit_if_failed_dup(t_cmd *s_cmd);
void	exit_if_failed_fork(t_cmd *s_cmd, int child);
void	path_error(t_cmd *s_cmd, char *av, char **path, char **cmd, int id);

//					FREE
void	free_pp_arr(char **tab);
void	free_struct(t_cmd *s_cmd);

#endif