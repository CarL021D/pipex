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
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/errno.h>

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

void    exit_if_not_5_args(int ac)
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

char    *get_command_path(char *av, char **envp)
{
    char    **segmented_path;
    char    *command_path;
    char    *path_env;
    char    **cmd;
    int     i;

    path_env = get_segmented_path(envp);
    segmented_path = ft_split(path_env, ':');
    free(path_env);
    // cmd = ft_split(av[2], ' ');
    cmd = ft_split(av, ' ');
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

void exit_if_failed_fork(t_cmd *s_cmd)
{
	if (s_cmd->pid1 == -1 || s_cmd->pid2 == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
}

void	child_1_exec(t_cmd *s_cmd, char **av, int *pipe_fd, char **envp)
{
	char    **cmd_options;
	// char    *cmd_path;
	int		fd;

	if (s_cmd->pid1 == 0)
	{
		close(pipe_fd[0]);
		fd = open(av[1], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		s_cmd->cmd1_path = get_command_path(av[2], envp);
		cmd_options = ft_split(av[2], ' ');
		write(2, "11\n", 3);
		if (execve(s_cmd->cmd1_path, cmd_options, envp) == -1)
		{
			perror("Execve");
			exit(EXIT_FAILURE);
		}
	}
}

void	child_2_exec(t_cmd *s_cmd, char **av, int *pipe_fd, char **envp)
{
    char    **cmd_options;
	// char    *cmd_path;
	int		fd;

	if (s_cmd->pid2 == 0)
	{
		close(pipe_fd[1]);
		fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		s_cmd->cmd2_path = get_command_path(av[3], envp);
		cmd_options = ft_split(av[3], ' ');
		close(pipe_fd[0]);
		write(2, "22\n", 3);
		if (execve(s_cmd->cmd2_path, cmd_options, envp) == -1)
		{
			perror("Execve");
			exit(EXIT_FAILURE);
		}
	}
}

// void	parent_process_exec(t_cmd *s_cmd, int *pipe_fd)
// {
// 	// (void)pid_1;
// 	(void)pid_2;
// 	waitpid(s_cmd->pid1, NULL, 0);
// 	// waitpid(pid_2, NULL, 0);
// 	close(pipe_fd[0]);
// 	// close(pipe_fd[1]);
// 	free_struct(s_cmd);
// 	write(2, "END\n", 4);
// }

// void	free_struct(t_cmd *s_cmd)
// {
// 	t_cmd	*s_tmp;
// 	int		i;

// 	s_tmp = s_cmd;
// 	i = 4;
// 	while (i)
// 	{
// 		if (*s_tmp != NULL)
// 			free(*s_tmp);
// 		s_tmp++;
// 		i--;
// 	}
// }

// void	init_struct(t_cmd *s_cmd)
// {
// 	t_cmd	*s_tmp;
// 	int		i;

// 	s_tmp = s_cmd;
// 	i = 4;
// 	while (i)
// 	{
// 		*s_tmp = NULL;
// 		s_tmp++;
// 		i--;
// 	}
// }

int	main(int ac, char **av, char **envp)
{
	t_cmd	s_cmd;
    // pid_t   pid_1;
	// pid_t	pid_2;
	int		pipe_fd[2];

    exit_if_not_5_args(ac);
	// init_cmd_struct(&s_cmd);
	if (pipe(pipe_fd) == -1)
		return(perror("Pipe"), 1);
	s_cmd.pid1 = fork();
	exit_if_failed_fork(&s_cmd);
	child_1_exec(&s_cmd, av, pipe_fd, envp);
	s_cmd.pid2 = fork();
	exit_if_failed_fork(&s_cmd);
	child_2_exec(&s_cmd, av, pipe_fd, envp);
	// waitpid(pid_2, &status, 0);
	printf("END\n");
	// parent_process_exec(&s_cmd, pipe_fd);
}
