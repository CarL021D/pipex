/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 23:47:31 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/16 03:02:22 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

// static void	close_fds(t_cmd *s_cmd, int last_fd)
// {
// 	int		fd_x;

// 	fd_x = 3 + (s_cmd->nb_cmd * 2) + last_fd;
// 	while (fd_x > 2)
// 	{
// 		close(fd_x);
// 		fd_x--;
// 	}
// }

void	close_fds(t_cmd *s_cmd, int fd)
{
	int		i;

	if (fd == 0)
		close(s_cmd->fd_in);
	if (fd == 1)
		close(s_cmd->fd_out);
	i = 0;
	while (i < (s_cmd->nb_cmd - 1))
	{
		close(s_cmd->pipe_arr[i][0]);
		close(s_cmd->pipe_arr[i][1]);
		i++;
	}
}

void	fd_to_pipe_exec(t_cmd *s_cmd, char **av)
{
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		fd_in_init(s_cmd, av);
		if (dup2(s_cmd->fd_in, STDIN_FILENO) == -1)
			exit_if_failed_dup();
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count][1], STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		close_fds(s_cmd, FD_IN);
		s_cmd->cmd_path = get_command_path(s_cmd, av[s_cmd->arg_index]);
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');		
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}


void	here_doc_to_pipe_exec(t_cmd *s_cmd, char **av)
{
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		set_here_doc(s_cmd, av);
		if (s_cmd->fd_in == -1)
		{
			perror("Fd");
			exit(EXIT_FAILURE);
		}
		if (dup2(s_cmd->pipe_here_doc[0], STDIN_FILENO) == -1)
		{
			write(2, "errorP\n", 7);
			exit_if_failed_dup();
		}
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count][1], STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		close_fds(s_cmd, FD_IN);
		s_cmd->cmd_path = get_command_path(s_cmd, av[s_cmd->arg_index]);
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}


void	pipe_to_pipe_exec(t_cmd *s_cmd, char **av)
{
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count - 1][0], STDIN_FILENO) == -1)
			exit_if_failed_dup();
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count][1], STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		close_fds(s_cmd, -1);
		s_cmd->cmd_path = get_command_path(s_cmd, av[s_cmd->arg_index]);
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}


void	pipe_to_fd_exec(t_cmd *s_cmd, char **av, int ac)
{
	fd_out_init(s_cmd, ac, av);
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{		
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count - 1][0], STDIN_FILENO) == -1)
			exit_if_failed_dup();
		if (dup2(s_cmd->fd_out, STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		close_fds(s_cmd, FD_OUT);
		s_cmd->cmd_path = get_command_path(s_cmd, av[s_cmd->arg_index]);
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}








// void	fd_to_pipe_exec(t_cmd *s_cmd, char **av)
// {
// 	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
// 	{
// 		fd_in_init(s_cmd, av);
//		close(s_cmd->pipe_[0]);
// 		if (s_cmd->fd_in == -1)
// 		{
// 			perror("Fd");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (dup2(s_cmd->fd_in, STDIN_FILENO) == -1)
// 			exit_if_failed_dup();
// 		close(s_cmd->fd_in);
// 		if (dup2(s_cmd->pipe_[1], STDOUT_FILENO) == -1)
// 			exit_if_failed_dup();
// 		close(s_cmd->pipe_[1]);
// 		s_cmd->cmd_path = get_command_path(s_cmd, av[s_cmd->arg_index]);
// 		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');		
// 		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
// 		perror("Execve");
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	here_doc_to_pipe_exec(t_cmd *s_cmd, char **av)
// {
// 	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
// 	{
// 		close(s_cmd->pipe_[0]);
// 		if (s_cmd->fd_in == -1)
// 		{
// 			perror("Fd");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (dup2(s_cmd->pipe_here_doc[0], STDIN_FILENO) == -1)
// 		{
// 			write(2, "errorP\n", 7);
// 			exit_if_failed_dup();
// 		}
// 		close(s_cmd->fd_in);
// 		if (dup2(s_cmd->pipe_[1], STDOUT_FILENO) == -1)
// 			exit_if_failed_dup();
// 		close(s_cmd->pipe_here_doc[0]);
// 		close(s_cmd->pipe_[1]);
// 		s_cmd->cmd_path = get_command_path(s_cmd, av[s_cmd->arg_index]);
// 		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
// 		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
// 		perror("Execve");
// 		exit(EXIT_FAILURE);
// 	}
// 	waitpid(s_cmd->pid_arr[s_cmd->fork_count], NULL, 0);
// }

// void	pipe_to_pipe_exec(t_cmd *s_cmd, char **av)
// {
// 	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
// 	{
// 		fd_in_init(s_cmd, av);
// 		// close(s_cmd->pipe_[0]);
// 		if (s_cmd->fd_in == -1)
// 		{
// 			perror("Fd");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (dup2(s_cmd->pipe_[0], STDIN_FILENO) == -1)
// 			exit_if_failed_dup();
// 		close(s_cmd->pipe_[0]);
// 		if (dup2(s_cmd->temp_pipe[0], s_cmd->pipe_[1]) == -1)
// 			exit_if_failed_dup();
// 		if (dup2(s_cmd->pipe_[0], s_cmd->temp_pipe[1]) == -1)
// 			exit_if_failed_dup();
// 		if (dup2(s_cmd->pipe_[1], STDOUT_FILENO) == -1)
// 			exit_if_failed_dup();
// 		close(s_cmd->temp_pipe[0]);
// 		close(s_cmd->temp_pipe[1]);
// 		close(s_cmd->pipe_[1]);
// 		s_cmd->cmd_path = get_command_path(s_cmd, av[s_cmd->arg_index]);
// 		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');		
// 		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
// 		perror("Execve");
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	pipe_to_fd_exec(t_cmd *s_cmd, char **av, int ac)
// {
// 	fd_out_init(s_cmd, ac, av);
// 	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
// 	{
// 		close(s_cmd->pipe_[1]);
// 		if (s_cmd->fd_out == -1)
// 			exit(EXIT_FAILURE);
// 		if (dup2(s_cmd->pipe_[0], STDIN_FILENO) == -1)
// 			exit_if_failed_dup();
// 		if (dup2(s_cmd->fd_out, STDOUT_FILENO) == -1)
// 			exit_if_failed_dup();
// 		close(s_cmd->pipe_[0]);
// 		close(s_cmd->fd_out);
// 		s_cmd->cmd_path = get_command_path(s_cmd, av[s_cmd->arg_index]);
// 		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
// 		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
// 		perror("Execve");
// 		exit(EXIT_FAILURE);
// 	}
// }