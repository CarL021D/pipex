/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:03:11 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/23 13:16:28 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_1_exec(t_cmd *s_cmd, char **envp)
{
	s_cmd->pid_1 = fork();
	exit_if_failed_fork(s_cmd, CHILD_1);
	if (s_cmd->pid_1 == 0)
	{
		exit_if_failed_fd_open(s_cmd, FD_IN);
		close(s_cmd->pipe_[0]);
		if (dup2(s_cmd->fd_in, STDIN_FILENO) == -1)
			exit_if_failed_dup(s_cmd);
		close(s_cmd->fd_in);
		if (dup2(s_cmd->pipe_[1], STDOUT_FILENO) == -1)
			exit_if_failed_dup(s_cmd);
		close(s_cmd->fd_in);
		close(s_cmd->pipe_[1]);
		execve(s_cmd->cmd_path, s_cmd->cmd_options, envp);
		perror("Execve");
	}
}

static void	child_2_exec(t_cmd *s_cmd, char **av, char **envp)
{
	init_fd(FD_OUT, s_cmd, av);
	s_cmd->pid_2 = fork();
	exit_if_failed_fork(s_cmd, CHILD_2);
	if (s_cmd->pid_2 == 0)
	{
		exit_if_failed_fd_open(s_cmd, FD_OUT);
		close(s_cmd->pipe_[1]);
		if (dup2(s_cmd->pipe_[0], STDIN_FILENO) == -1)
			exit_if_failed_dup(s_cmd);
		if (dup2(s_cmd->fd_out, STDOUT_FILENO) == -1)
			exit_if_failed_dup(s_cmd);
		close(s_cmd->fd_in);
		close(s_cmd->fd_out);
		close(s_cmd->pipe_[0]);
		execve(s_cmd->cmd_path, s_cmd->cmd_options, envp);
		perror("Execve");
	}
}

static void	exec_parent_process(t_cmd *s_cmd)
{
	close(s_cmd->fd_in);
	if (s_cmd->fd_in)
		close(s_cmd->fd_out);
	free_execve_params(s_cmd);
	close(s_cmd->pipe_[0]);
	close(s_cmd->pipe_[1]);
	waitpid(s_cmd->pid_1, NULL, 0);
	waitpid(s_cmd->pid_2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	s_cmd;

	exit_if_not_5_args(ac);
	init_cmd_struct(&s_cmd, envp);
	if (pipe(s_cmd.pipe_) == -1)
		return (perror("Pipe"), 1);
	init_fd(FD_IN, &s_cmd, av);
	s_cmd.cmd_path = get_cmd_path(&s_cmd, av[2]);
	s_cmd.cmd_options = ft_split(av[2], ' ');
	if (s_cmd.cmd_path != NULL)
		child_1_exec(&s_cmd, envp);
	free_execve_params(&s_cmd);
	s_cmd.cmd_path = get_cmd_path(&s_cmd, av[3]);
	s_cmd.cmd_options = ft_split(av[3], ' ');
	if (s_cmd.cmd_path != NULL)
		child_2_exec(&s_cmd, av, envp);
	exec_parent_process(&s_cmd);
}
