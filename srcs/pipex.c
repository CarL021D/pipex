/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:03:11 by caboudar          #+#    #+#             */
/*   Updated: 2022/10/12 21:04:59 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

#include <unistd.h>
// #include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

char	*join_slash_and_comd_to_path(char *s1, char *s2)
{
	char	*str;
	size_t	l_s1;
	size_t	l_s2;
	size_t	i;
	size_t	j;

	l_s1 = ft_strlen((char *)s1);
	l_s2 = ft_strlen((char *)s2);    
	str = malloc(sizeof(char) * (l_s1 + l_s2 + 2));
    // FREE
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < l_s1)
		str[i] = (char)s1[i];
    str[i] = '/';
    i++;
	while (++j < l_s2)
		str[i++] = (char)s2[j];
	str[i] = '\0';
	return (str);
}

void    check_args(int ac)
{
    if (ac < 2)
    {
        write(1, "Not enough arguments\n", 21);
        exit(EXIT_FAILURE);
    }
}

char    *get_command_path(char **envp, char **av)
{
    char    **segmented_path;
    char    *command_path;
    char    *path_env;
    int     i;

    i = -1;
    while (envp[++i])
    {
        path_env = ft_strnstr(envp[i], "PATH=", 5);
        if (path_env)
            break ;
    }
    segmented_path = ft_split(path_env, ':');
    free(path_env);
    if (!envp[i])
        exit(EXIT_FAILURE);
    i = -1;
    while (segmented_path[++i])
    {
        command_path = join_slash_and_comd_to_path(segmented_path[i], av[1]);
        if (access(command_path, F_OK | X_OK) == 0)
            return (command_path);
    }
    free(command_path);
    exit(EXIT_FAILURE);
}

char    **get_excve_args(char **av)
{
    char    **cmd_line_parsed;
    
    cmd_line_parsed = ft_split(av[1], ' ');
    return (cmd_line_parsed);
}



int main(int ac, char **av, char **envp)
{
    char    *command_path;

    char *execve_args[3] = {"ls", "-la", NULL};
    // char *execve_args[3];
	
    // char **options;
    // int     i;
    
    // t_data  data;

    check_args(ac);
    command_path = get_command_path(envp, av);

    // options = ft_split(av[1], ' ');
    // *execve_args = {options[0], options[1], NULL};
    // execve_args[0] = options[0];
    // execve_args[1] = options[1];
    // execve_args[2] = n;
    
    // for (int i = 0; execve_args[i]; i++)
        // printf("%s\n", execve_args[i]);

    // execve_args = get_excve_args(av);
    // (void)execve_args;
    // for (int i = 0; execve_args[i]; i++)
        // printf("%s\n", execve_args[i]);
    // printf("%s\n", command_path);
    execve(command_path, execve_args, envp);
}
