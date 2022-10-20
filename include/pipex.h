/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:58:48 by caboudar          #+#    #+#             */
/*   Updated: 2022/10/20 15:27:15 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define CHILD_1 1
# define CHILD_2 2

typedef struct  s_cmd
{
    pid_t   pid1;
    pid_t   pid2;
    char    *cmd1_path;
    char    *cmd2_path;
    char    **cmd1_options;
    char    **cmd2_options;
}   t_cmd;

//                  PIPEX
void    exit_if_not_5_args(int ac);
char    *get_command_path(char *av, char **envp);

//                  UTILS
size_t  ft_strlen(char *str);
// void    free_tab(char **arr, int i);
// int	    ft_word_len(char *str, char charset);
// int	    ft_word_count(char *str, char charset);
// char	*ft_malloc_word(char *str, char charset);
char	**ft_split(char *str, char c);


//                  PATH PARSING
// char    *cmd_env_path_line(char **envp);
char    *path_str(char *full_path);
char	*ft_strnstr(char *full_path, const char *s2, size_t n);
// char	*join_slash_and_comd_to_path(char *s1, char *s2);

//                  ERROR
void	exit_if_failed_dup();
void	exit_if_failed_fork(t_cmd *s_cmd, int child);

//                  FREE
void    free_double_tab(char **tab);
void	free_struct(t_cmd *s_cmd);

#endif