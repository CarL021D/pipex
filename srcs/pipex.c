/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:03:11 by caboudar          #+#    #+#             */
/*   Updated: 2022/10/12 23:26:53 by caboudar         ###   ########.fr       */
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

char    *get_segmented_path(char **envp)
{
    char    *path_env;
    int     i;

    i = 0;
    while (envp[i])
    {
        path_env = ft_strnstr(envp[i], "PATH=", 5);
        if (path_env)
            return (path_env);
        i++;
    }
    exit(EXIT_FAILURE);
}

char    *get_command_path(char **envp, char **av)
{
    char    **segmented_path;
    char    *command_path;
    char    *path_env;
    char    **cmd;
    int     i;

    path_env = get_segmented_path(envp);
    segmented_path = ft_split(path_env, ':');
    free(path_env);
    cmd = ft_split(av[1], ' ');
    i = 0;
    while (segmented_path[i])
    {
        command_path = join_slash_and_comd_to_path(segmented_path[i], cmd[0]);
        if (access(command_path, F_OK | X_OK) == 0)
        {
            free(segmented_path);
            return (command_path);
        }
        i++;
    }

    // SECURE EVTHG ???
    
    free(segmented_path);
    free(command_path);
    exit(EXIT_FAILURE);
}



int main(int ac, char **av, char **envp)
{
    pid_t   pid;
    char    *command_path;	
    char    **cmd_options;

    check_args(ac);
    pid = fork();
    command_path = get_command_path(envp, av);
    cmd_options = ft_split(av[1], ' ');
    if (pid == 0)
	{
		printf("Son >>> %d\n", pid);
		execve(command_path, cmd_options, envp);
	}
	waitpid(pid, NULL, 0);
	printf("Dad >>> %d\n", pid);
}
