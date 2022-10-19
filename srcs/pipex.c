/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:03:11 by caboudar          #+#    #+#             */
/*   Updated: 2022/10/19 22:11:54 by caboudar         ###   ########.fr       */
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
	char		*str;
	size_t		l_s1;
	size_t		l_s2;
	size_t		i;
	size_t		j;

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
	if (ac != 5)
	{
		write(1, "5 arguments are required\n", 26);
		exit(EXIT_FAILURE);
	}
}

char    *get_segmented_path(char **envp)
{
	char	*path_env;
	int		i;

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

void	exit_if_failed_dup()
{
		perror("Dup2");
		exit(EXIT_FAILURE);
}

void	exit_if_failed_fork(t_cmd *s_cmd, int child)
{
	if (child == 1 && s_cmd->pid1 == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
	if (child == 2 && s_cmd->pid2 == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
}

char    *get_command_path(char *av, char **envp)
{
	char	**segmented_path;
	char	*command_path;
	char	*path_env;
	char	**cmd;
	int		i;

	path_env = get_segmented_path(envp);
	segmented_path = ft_split(path_env, ':');
	free(path_env);
	cmd = ft_split(av, ' ');
	i = 0;
	while (segmented_path[i])
	{
		command_path = join_slash_and_comd_to_path(segmented_path[i], cmd[0]);
		if (access(command_path, F_OK | X_OK) == 0)
		{
			free_double_tab(segmented_path);
			return (command_path);
		}
		i++;
	}
	free_double_tab(segmented_path);
	free(command_path);
	exit(EXIT_FAILURE);
}

void	child_1_exec(t_cmd *s_cmd, char **av, int *pipe_fd, char **envp)
{
	int		fd;

	if (s_cmd->pid1 == 0)
	{
		close(pipe_fd[0]);
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd, STDIN_FILENO) == -1)
			exit_if_failed_dup();
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		s_cmd->cmd1_path = get_command_path(av[2], envp);
		free(get_command_path(av[2], envp));
		s_cmd->cmd1_options = ft_split(av[2], ' ');
		write(2, "11\n", 3);
		if (execve(s_cmd->cmd1_path, s_cmd->cmd1_options, envp) == -1)
		{
			perror("Execve");
			exit(EXIT_FAILURE);
		}
	}
}

void	child_2_exec(t_cmd *s_cmd, char **av, int *pipe_fd, char **envp)
{
	int		fd;

	if (s_cmd->pid2 == 0)
	{
		close(pipe_fd[1]);
		fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			exit_if_failed_dup();
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		s_cmd->cmd2_path = get_command_path(av[3], envp);
		free(get_command_path(av[3], envp));
		s_cmd->cmd2_options = ft_split(av[3], ' ');
		close(pipe_fd[0]);
		write(2, "22\n", 3);
		if (execve(s_cmd->cmd2_path, s_cmd->cmd2_options, envp) == -1)
		{
			perror("Execve");
			exit(EXIT_FAILURE);
		}
	}
}

void	parent_process_exec(t_cmd *s_cmd, int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	free_struct(s_cmd);
	waitpid(s_cmd->pid1, NULL, 0);
	waitpid(s_cmd->pid2, NULL, 0);
	write(2, "END\n", 4);
}

void	init_cmd_struct(t_cmd *s_cmd)
{
	s_cmd->cmd1_path = NULL;
	s_cmd->cmd2_path = NULL;
	s_cmd->cmd1_options = NULL;
	s_cmd->cmd2_options = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	s_cmd;
	int		pipe_fd[2];

	exit_if_not_5_args(ac);
	init_cmd_struct(&s_cmd);
	if (pipe(pipe_fd) == -1)
		return(perror("Pipe"), 1);
	s_cmd.pid1 = fork();
	exit_if_failed_fork(&s_cmd, CHILD_1);
	child_1_exec(&s_cmd, av, pipe_fd, envp);
	s_cmd.pid2 = fork();
	exit_if_failed_fork(&s_cmd, CHILD_2);
	child_2_exec(&s_cmd, av, pipe_fd, envp);
	parent_process_exec(&s_cmd, pipe_fd);
}
