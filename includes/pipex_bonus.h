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
# define BUFFER_SIZE 10

typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;


	// try setting pipe into the structure 
	int		pipe_[2];
	int		temp_pipe[2];

	char	*cmd_path;
	
	char	**cmd_options;
	char	**env_p;
	int		nb_cmd;

	// index going through each arguments
	int		arg_index;

	// number of fork that are stored inside the pid array
	int		fork_count;
	pid_t	*pid_arr;

	int		here_doc;
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
void	exit_if_failed_fork(t_cmd *s_cmd);

//                  FREE
void	free_cmd_line(t_cmd *s_cmd);
void	free_double_tab(char **tab);
void	free_struct(t_cmd *s_cmd);

//					GET NEXT LINE
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *buffer);
int		still_on_line(char *stash);

#endif