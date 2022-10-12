/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:58:48 by caboudar          #+#    #+#             */
/*   Updated: 2022/10/12 19:50:08 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0

// typedef struct s_data
// {
//     char *path;

//     char *cmd_name;
//     char *cmd_option;
// }   t_data;

//                  PIPEX
void    check_args(int ac);
char    *get_command_path(char **envp, char **av);


//                  UTILS
size_t  ft_strlen(char *str);
void    free_tab(char **arr, int i);
int	    ft_word_len(char *str, char charset);
int	    ft_word_count(char *str, char charset);
char	*ft_malloc_word(char *str, char charset);
char	**ft_split(char *str, char c);


//                  PATH PARSING
char    *path_str(char *full_path);
char	*ft_strnstr(char *full_path, const char *s2, size_t n);
char	*join_slash_and_comd_to_path(char *s1, char *s2);

#endif