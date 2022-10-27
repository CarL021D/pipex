

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

// // void stock_fork_pid(t_cmd *s_cmd, pid_t pid)
// // {
// // 	int		*tab;
// // 	int		i;

// // 	if (pid == 0)
// // 		return ;
// // 	tab = malloc(sizeof(int) * s_cmd->fork_count + 1);
// // 	if (!tab)
// // 		exit(EXIT_FAILURE);
// // 	i = 0;
// // 	while (i < s_cmd->fork_count)
// // 	{
// // 		tab[i] = s_cmd->pid_arr[i];
// // 		i++;
// // 	}
// // 	tab[i] = pid;
// // 	if (s_cmd->fork_count)
// // 		free(s_cmd->pid_arr);
// // 	s_cmd->pid_arr = tab;
// // 	free(tab);
// // }



int	str_cmp(const char *s1, const char *s2)
{
	char			*str_1;
	char			*str_2;
	int				i;

	str_1 = (char *)s1;
	str_2 = (char *)s2;
	i = 0;
	while ((str_1[i] || str_2[i]) && str_1[i] == str_2[i])
		i++;
	if (str_1[i] == '\0' && str_2[i] == '\0')
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
	s_cmd->cmd_path = malloc(sizeof(char *) * s_cmd->nb_cmd);
	if (!s_cmd->cmd_path)
		exit(EXIT_FAILURE);
	s_cmd->cmd_options = malloc(sizeof(char *) * s_cmd->nb_cmd);
	if (!s_cmd->cmd_options)
		exit(EXIT_FAILURE);
	s_cmd->pid_arr = malloc(sizeof(pid_t) * (ac - s_cmd->arg_index));
	if (!s_cmd->pid_arr)
		exit(EXIT_FAILURE);

	// s_cmd->pid_index = 0;
}

void pass_fd_to_pipe(t_cmd *s_cmd, char **av, int *pipe_, char **envp)
{
	// if (s_cmd->pid_1 == 0)
	// {
	// 	close(pipe_[0]);
	// 	if (s_cmd->fd_in == -1)
	// 	{
	// 		perror("Fd");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	if (dup2(s_cmd->fd_in, STDIN_FILENO) == -1)
	// 		exit_if_failed_dup();
	// 	close(s_cmd->fd_in);
	// 	if (dup2(pipe_[1], STDOUT_FILENO) == -1)
	// 		exit_if_failed_dup();
	// 	s_cmd->cmd_path = get_command_path(av[2], envp);
	// 	free(get_command_path(av[2], envp));
	// 	s_cmd->cmd_options = ft_split(av[2], ' ');
	// 	close(pipe_[1]);
	// 	s_cmd->arg_index++;
	// 	s_cmd->fork_count++;
	// 	execve(s_cmd->cmd_path, s_cmd->cmd_options, envp);
	// 	perror("Execve");
	// 	exit(EXIT_FAILURE);
	// }

	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
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
		s_cmd->cmd_path = get_command_path(av[s_cmd->arg_index], envp);
		// s_cmd->cmd_path = get_command_path(av[s_cmd->arg_index], envp);
		// free(get_command_path(av[s_cmd->arg_index], envp));
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
		close(pipe_[1]);
		execve(s_cmd->cmd_path, s_cmd->cmd_options, envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}

void	exec_process(t_cmd *s_cmd, int ac, char **av, int *pipe_, char **envp)
{
	(void)ac;
	// if (s_cmd->pid_2 == 0)
	// {
	// 	close(s_cmd->fd_in);
	// 	if (s_cmd->fd_out == -1)
	// 		exit(EXIT_FAILURE);
	// 	if (dup2(pipe_[0], STDIN_FILENO) == -1)
	// 		exit_if_failed_dup();
	// 	if (s_cmd->arg_index < (ac - 2))
	// 	{
	// 		if (dup2(pipe_[1], STDOUT_FILENO) == -1)
	// 		exit_if_failed_dup();
	// 	// }
	// 	// else
	// 		// if (dup2(s_cmd->fd_out, STDOUT_FILENO) == -1)
	// 		// 	exit_if_failed_dup();
	// 	close(s_cmd->fd_out);
	// 	s_cmd->cmd_path = get_command_path(av[3], envp);
	// 	free(get_command_path(av[3], envp));
	// 	s_cmd->cmd_options = ft_split(av[3], ' ');
	// 	close(pipe_[0]);
	// 	close(pipe_[1]);
	// 	s_cmd->fork_count++;
	// 	execve(s_cmd->cmd_path, s_cmd->cmd_options, envp);
	// 	perror("Execve");
	// 	exit(EXIT_FAILURE);

	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		close(pipe_[1]);
		close(s_cmd->fd_in);
		if (s_cmd->fd_out == -1)
			exit(EXIT_FAILURE);
		if (dup2(pipe_[0], STDIN_FILENO) == -1)
			exit_if_failed_dup();
		if (dup2(s_cmd->fd_out, STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		close(s_cmd->fd_out);
		s_cmd->cmd_path = get_command_path(av[s_cmd->arg_index], envp);
		free(get_command_path(av[s_cmd->arg_index], envp));
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
		close(pipe_[0]);
		execve(s_cmd->cmd_path, s_cmd->cmd_options, envp);
		perror("Execve");
		exit(EXIT_FAILURE);

	}
}

void	e(t_cmd *s_cmd, int ac, char **av, int *pipe_, char **envp)
{
	(void)ac;
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		close(s_cmd->fd_in);
		if (s_cmd->fd_out == -1)
			exit(EXIT_FAILURE);
		if (dup2(pipe_[0], STDIN_FILENO) == -1)
			exit_if_failed_dup();
		// if (s_cmd->arg_index < (ac - 2))
		// {
			// if (dup2(pipe_[1], STDOUT_FILENO) == -1)
			// exit_if_failed_dup();
		// }
		// else
		if (dup2(s_cmd->fd_out, STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		close(s_cmd->fd_out);
		s_cmd->cmd_path = get_command_path(av[s_cmd->arg_index], envp);
		free(get_command_path(av[s_cmd->arg_index], envp));
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
		close(pipe_[0]);
		close(pipe_[1]);
		s_cmd->fork_count++;
		execve(s_cmd->cmd_path, s_cmd->cmd_options, envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}


// void	wait_for_child_process(t_cmd *s_cmd)
// {
// 	int		i;

// 	i = 0;
// 	while (i < s_cmd->fork_count)
// 	{
// 		waitpid(s_cmd->pid_arr[i], NULL, 0);
// 		i++;
// 	}
// }

// void	exec_parent_process(t_cmd *s_cmd, int *pipe_)
// {
// 	close(s_cmd->fd_in);
// 	close(s_cmd->fd_out);
// 	close(pipe_[0]);
// 	close(pipe_[1]);
// 	// free_struct(s_cmd);
// 	// wait_for_child_process(s_cmd);
// }

int main(int ac, char **av, char **envp)
{
	t_cmd	s_cmd;
	int		pipe_[2];

	exit_if_less_than_5_args(ac);
	init_cmd_struct(&s_cmd, ac, av);
	if (pipe(pipe_) == -1)
		return (perror("Pipe"), 1);
	s_cmd.fd_in = open(av[s_cmd.arg_index], O_RDONLY);
	s_cmd.fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	s_cmd.arg_index++;
	while (s_cmd.fork_count < s_cmd.nb_cmd)
	{
		if (s_cmd.fork_count == 0)
		{
			s_cmd.pid_arr[s_cmd.fork_count] = fork();
			exit_if_failed_fork(&s_cmd, CHILD_1);
			pass_fd_to_pipe(&s_cmd, av, pipe_, envp);		
		}	
		else if (s_cmd.fork_count == (s_cmd.nb_cmd - 1))
		{
			s_cmd.pid_arr[s_cmd.fork_count] = fork();
			exit_if_failed_fork(&s_cmd, CHILD_2);
			e(&s_cmd, ac, av, pipe_, envp);
		}
		else
		{
			s_cmd.pid_arr[s_cmd.fork_count] = fork();
			exit_if_failed_fork(&s_cmd, CHILD_2);
			e(&s_cmd, ac, av, pipe_, envp);
		}
		free_cmd_line(&s_cmd);
		s_cmd.arg_index++;
		s_cmd.fork_count++;
	}
// 	// exec_parent_process(&s_cmd, pipe_);
}
