/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:58:48 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/19 21:07:42 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define CHILD_1 1
# define CHILD_2 2
# define FD_IN 0
# define FD_OUT 1

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
void	error_no_path(t_cmd *s_cmd, char *av, char **path, char **cmd, int i);

//					FREE
void	free_double_tab(char **tab);
void	free_struct(t_cmd *s_cmd);

#endif