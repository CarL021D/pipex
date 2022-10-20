/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:03:11 by caboudar          #+#    #+#             */
/*   Updated: 2022/10/20 15:27:07 by caboudar         ###   ########.fr       */
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

static void	init_cmd_struct(t_cmd *s_cmd)
{
	s_cmd->cmd1_path = NULL;
	s_cmd->cmd2_path = NULL;
	s_cmd->cmd1_options = NULL;
	s_cmd->cmd2_options = NULL;
}

static void	child_1_exec(t_cmd *s_cmd, char **av, int *pipe_, char **envp)
{
	int		fd;

	if (s_cmd->pid1 == 0)
	{
		close(pipe_[0]);
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd, STDIN_FILENO) == -1)
			exit_if_failed_dup();
		if (dup2(pipe_[1], STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		s_cmd->cmd1_path = get_command_path(av[2], envp);
		free(get_command_path(av[2], envp));
		s_cmd->cmd1_options = ft_split(av[2], ' ');
		close(pipe_[1]);
		write(2, "11\n", 3);
		execve(s_cmd->cmd1_path, s_cmd->cmd1_options, envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}

static void	child_2_exec(t_cmd *s_cmd, char **av, int *pipe_, char **envp)
{
	int		fd;

	if (s_cmd->pid2 == 0)
	{
		close(pipe_[1]);
		fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (dup2(pipe_[0], STDIN_FILENO) == -1)
			exit_if_failed_dup();
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		s_cmd->cmd2_path = get_command_path(av[3], envp);
		free(get_command_path(av[3], envp));
		s_cmd->cmd2_options = ft_split(av[3], ' ');
		close(pipe_[0]);
		write(2, "22\n", 3);
		execve(s_cmd->cmd2_path, s_cmd->cmd2_options, envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}

static void	parent_process_exec(t_cmd *s_cmd, int *pipe_)
{
	close(pipe_[0]);
	close(pipe_[1]);
	free_struct(s_cmd);
	waitpid(s_cmd->pid1, NULL, 0);
	waitpid(s_cmd->pid2, NULL, 0);
	write(2, "END\n", 4);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	s_cmd;
	int		pipe_[2];

	exit_if_not_5_args(ac);
	init_cmd_struct(&s_cmd);
	if (pipe(pipe_) == -1)
		return(perror("Pipe"), 1);
	s_cmd.pid1 = fork();
	exit_if_failed_fork(&s_cmd, CHILD_1);
	child_1_exec(&s_cmd, av, pipe_, envp);
	s_cmd.pid2 = fork();
	exit_if_failed_fork(&s_cmd, CHILD_2);
	child_2_exec(&s_cmd, av, pipe_, envp);
	parent_process_exec(&s_cmd, pipe_);
}
