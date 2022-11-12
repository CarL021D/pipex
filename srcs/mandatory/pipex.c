/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:03:11 by caboudar          #+#    #+#             */
/*   Updated: 2022/10/24 16:01:04 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/errno.h>


// Maybe to remove because allocation are made inside child so no need to free
static void	init_cmd_struct(t_cmd *s_cmd)
{
	s_cmd->cmd1_path = NULL;
	s_cmd->cmd2_path = NULL;
	s_cmd->cmd1_options = NULL;
	s_cmd->cmd2_options = NULL;
}

// Set fd in open inside a child process to avoid to have to close it inside 
// on other processes

static void	child_1_exec(t_cmd *s_cmd, char **av, int *pipe_, char **envp)
{
	if (s_cmd->pid_1 == 0)
	{
		// Added lign 40
		s_cmd->fd_in = open(av[1], O_RDONLY);
		close(pipe_[0]);
		if (s_cmd->fd_in == -1)
		{
			perror("Fd");
			exit(EXIT_FAILURE);
		}
		if (dup2(s_cmd->fd_in, STDIN_FILENO) == -1)
			exit_if_failed_dup();
		close(s_cmd->fd_in);
		if (dup2(pipe_[1], STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		s_cmd->cmd1_path = get_command_path(av[2], envp);
		s_cmd->cmd1_options = ft_split(av[2], ' ');
		close(pipe_[1]);
		execve(s_cmd->cmd1_path, s_cmd->cmd1_options, envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}

static void	child_2_exec(t_cmd *s_cmd, char **av, int *pipe_, char **envp)
{
	if (s_cmd->pid_2 == 0)
	{
		// Added lign 66
		s_cmd->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(pipe_[1]);
		if (s_cmd->fd_out == -1)
			exit(EXIT_FAILURE);
		if (dup2(pipe_[0], STDIN_FILENO) == -1)
			exit_if_failed_dup();
		if (dup2(s_cmd->fd_out, STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		close(s_cmd->fd_out);
		s_cmd->cmd2_path = get_command_path(av[3], envp);
		s_cmd->cmd2_options = ft_split(av[3], ' ');
		close(pipe_[0]);
		execve(s_cmd->cmd2_path, s_cmd->cmd2_options, envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}

static void	exec_parent_process(t_cmd *s_cmd, int *pipe_)
{
	// close(s_cmd->fd_in);
	// close(s_cmd->fd_out);
	close(pipe_[0]);
	close(pipe_[1]);
	free_struct(s_cmd);
	waitpid(s_cmd->pid_1, NULL, 0);
	waitpid(s_cmd->pid_2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	s_cmd;
	int		pipe_[2];

	exit_if_not_5_args(ac);
	init_cmd_struct(&s_cmd);
	if (pipe(pipe_) == -1)
		return (perror("Pipe"), 1);
	// s_cmd.fd_in = open(av[1], O_RDONLY);
	s_cmd.pid_1 = fork();
	exit_if_failed_fork(&s_cmd, CHILD_1);
	child_1_exec(&s_cmd, av, pipe_, envp);
	// s_cmd.fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	s_cmd.pid_2 = fork();
	exit_if_failed_fork(&s_cmd, CHILD_2);
	child_2_exec(&s_cmd, av, pipe_, envp);
	exec_parent_process(&s_cmd, pipe_);
}
