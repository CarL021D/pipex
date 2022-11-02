

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipex.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/10/05 08:03:11 by caboudar          #+#    #+#             */
// /*   Updated: 2022/10/20 17:09:25 by caboudar         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/pipex_bonus.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/errno.h>

int	str_cmp(char *s1, char *s2)
{
	int				i;

	i = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}

static void	init_cmd_struct(t_cmd *s_cmd, int ac, char **av)
{
	if (str_cmp(av[1], "here_doc"))
	{
		s_cmd->here_doc = 1;
		s_cmd->arg_index = 2;
		s_cmd->nb_cmd = ac - 2;
	}
	else
	{
		s_cmd->here_doc = 0;
		s_cmd->arg_index = 1;
		s_cmd->nb_cmd = ac - 3;
	}
	s_cmd->fork_count = 0;
	// s_cmd->pipe_ = malloc(sizeof(int) * 2);
	// if (!s_cmd->s_cmd->pipe_)
	// 	exit(EXIT_FAILURE);
	// s_cmd->temp_s_cmd->pipe_ = malloc(sizeof(int) * 2);
	// if (!s_cmd->temp_s_cmd->pipe_)
	// 	exit(EXIT_FAILURE);
	s_cmd->cmd_path = malloc(sizeof(char *) * s_cmd->nb_cmd);
	if (!s_cmd->cmd_path)
		exit(EXIT_FAILURE);
	s_cmd->cmd_options = malloc(sizeof(char *) * s_cmd->nb_cmd);
	if (!s_cmd->cmd_options)
		exit(EXIT_FAILURE);
	s_cmd->pid_arr = malloc(sizeof(pid_t) * (ac - s_cmd->arg_index));
	if (!s_cmd->pid_arr)
		exit(EXIT_FAILURE);
}

void	here_doc_to_pipe(t_cmd *s_cmd, char **av, char **envp)
{
	char	*line;
	// int		fd_in;
	int		tmp_fd;
	int		i;

	i = 0;

	// TO set outide of fork
	tmp_fd = open(".temp_here_doc", O_WRONLY | O_CREAT | O_APPEND);
	// if (tmp_fd < 0)
	// 	set error
	// fd_in = dup(STDIN_FILENO);
	line = get_next_line(STDIN_FILENO);
	printf("line %s\n", line);
	while (!str_cmp(av[s_cmd->arg_index], line))
	{
		printf("111\n");

		write(1, "heredoc >", 9);
		write(s_cmd->fd_in, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	// -----------------------------------//
	if (dup2(s_cmd->pipe_[1], STDOUT_FILENO) == -1)
			exit_if_failed_dup();




	s_cmd->arg_index++;
	s_cmd->cmd_path = get_command_path(av[s_cmd->arg_index], envp);
	s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
	close(s_cmd->pipe_[1]);
	execve(s_cmd->cmd_path, s_cmd->cmd_options, envp);
	perror("Execve");
	exit(EXIT_FAILURE);
}

void	fd_to_pipe(t_cmd *s_cmd, char **av, char **envp)
{
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		close(s_cmd->pipe_[0]);
		close(s_cmd->temp_pipe[0]);
		if (s_cmd->fd_in == -1)
		{
			perror("Fd");
			exit(EXIT_FAILURE);
		}
		if (dup2(s_cmd->fd_in, STDIN_FILENO) == -1)
			exit_if_failed_dup();
		close(s_cmd->fd_in);
		if (dup2(s_cmd->temp_pipe[1], STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		s_cmd->cmd_path = get_command_path(av[s_cmd->arg_index], envp);
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
		close(s_cmd->temp_pipe[1]);
		execve(s_cmd->cmd_path, s_cmd->cmd_options, envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}

void	exec_process(t_cmd *s_cmd, char **av, char **envp)
{
	exit_if_failed_fork(s_cmd);
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		// close(s_cmd->temp_pipe[1]);
		// close(s_cmd->fd_in);
		if (s_cmd->fd_out == -1)
			exit(EXIT_FAILURE);
		if (dup2(s_cmd->temp_pipe[0], STDIN_FILENO) == -1)
			exit_if_failed_dup();
		if (s_cmd->fork_count < (s_cmd->nb_cmd - 1))
		{
			if (dup2(s_cmd->temp_pipe[1], STDOUT_FILENO) == -1)
				exit_if_failed_dup();
		}
		else if (dup2(s_cmd->fd_out, STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		close(s_cmd->fd_out);
		s_cmd->cmd_path = get_command_path(av[s_cmd->arg_index], envp);
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
		close(s_cmd->temp_pipe[0]);
		execve(s_cmd->cmd_path, s_cmd->cmd_options, envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}

// void	e(t_cmd *s_cmd, char **av, int *s_cmd->pipe_, char **envp)
// {
// 	exit_if_failed_fork(s_cmd);
// 	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
// 	{
// 		close(s_cmd->fd_in);
// 		if (s_cmd->fd_out == -1)
// 			exit(EXIT_FAILURE);
// 		if (dup2(s_cmd->pipe_[0], STDIN_FILENO) == -1)
// 			exit_if_failed_dup();
// 		if (dup2(s_cmd->fd_out, STDOUT_FILENO) == -1)
// 			exit_if_failed_dup();
// 		close(s_cmd->fd_out);
// 		s_cmd->cmd_path = get_command_path(av[s_cmd->arg_index], envp);
// 		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
// 		close(s_cmd->pipe_[0]);
// 		close(s_cmd->pipe_[1]);
// 		s_cmd->fork_count++;
// 		execve(s_cmd->cmd_path, s_cmd->cmd_options, envp);
// 		perror("Execve");
// 		exit(EXIT_FAILURE);
// 	}
// }


void	wait_for_child_process(t_cmd *s_cmd)
{
	int		i;

	i = 0;
	while (i < s_cmd->fork_count)
	{
		waitpid(s_cmd->pid_arr[i], NULL, 0);
		i++;
	}
}

void	exec_parent_process(t_cmd *s_cmd)
{
	close(s_cmd->fd_in);
	close(s_cmd->fd_out);
	close(s_cmd->pipe_[0]);
	close(s_cmd->pipe_[1]);
	// free_struct(s_cmd);
	wait_for_child_process(s_cmd);
}

int main(int ac, char **av, char **envp)
{
	t_cmd	s_cmd;

	exit_if_less_than_5_args(ac);
	init_cmd_struct(&s_cmd, ac, av);
	if (pipe(s_cmd.pipe_) == -1)
		return (perror("Pipe"), 1);
	if (s_cmd.here_doc)
	{
		s_cmd.fd_in = open(".temp_here_doc", O_RDONLY);
		s_cmd.fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		s_cmd.fd_in = open(av[s_cmd.arg_index], O_RDONLY);
		s_cmd.fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}

	s_cmd.arg_index++;
	while (s_cmd.fork_count < s_cmd.nb_cmd)
	{
		if (s_cmd.fork_count == 0)
		{
			s_cmd.pid_arr[s_cmd.fork_count] = fork();
			if (s_cmd.here_doc)
				here_doc_to_pipe(&s_cmd, av, envp);
			else
				fd_to_pipe(&s_cmd, av, envp);		
		}	
		else
		{
			s_cmd.pid_arr[s_cmd.fork_count] = fork();
			exec_process(&s_cmd, av, envp);
		}
		// printf("%d < %d \n", s_cmd.fork_count, s_cmd.nb_cmd);
		s_cmd.arg_index++;
		s_cmd.fork_count++;
	}

	exec_parent_process(&s_cmd);
}
