/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:58:48 by caboudar          #+#    #+#             */
/*   Updated: 2022/10/24 18:27:23 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define CHILD_1 1
# define CHILD_2 2

typedef struct s_cmd
{
	pid_t	pid_1;
	pid_t	pid_2;
	pid_t	pid_3;
	int		fd_1;
	int		fd_2;
	char	*cmd1_path;
	char	*cmd2_path;
	char	*cmd3_path;
	char	**cmd1_options;
	char	**cmd2_options;
	char	**cmd3_options;
	char	**env_p;
	
	int		cmd_nb;
	int		cmd_count;

	pid_t	*pid_arr;
	int		pid_count;
}	t_cmd;

//                  PIPEX
void	exit_if_less_than_5_args(int ac);
char	*get_command_path(char *av, char **envp);

//                  UTILS
size_t	ft_strlen(char *str);
char	**ft_split(char *str, char c);

//                  PATH PARSING
char	*path_str(char *full_path);
char	*ft_strnstr(char *full_path, const char *s2, size_t n);

//                  ERROR
void	exit_if_failed_dup(void);
void	exit_if_failed_fork(t_cmd *s_cmd, int child);

//                  FREE
void	free_double_tab(char **tab);
void	free_struct(t_cmd *s_cmd);

#endif