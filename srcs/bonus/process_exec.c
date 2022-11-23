/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 23:47:31 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/23 13:14:19 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fd_to_pipe_exec(t_cmd *s_cmd)
{
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		if (dup2(s_cmd->fd_in, STDIN_FILENO) == -1)
			exit_error(DUP2, s_cmd);
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count][1], STDOUT_FILENO) == -1)
			exit_error(DUP2, s_cmd);
		close(s_cmd->fd_in);
		close_fds(s_cmd);
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		exit_error(EXECVE, s_cmd);
	}
}

void	here_doc_to_pipe_exec(t_cmd *s_cmd)
{
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		if (dup2(s_cmd->pipe_here_doc[0], STDIN_FILENO) == -1)
			exit_error(DUP2, s_cmd);
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count][1], STDOUT_FILENO) == -1)
			exit_error(DUP2, s_cmd);
		close_here_doc_fd(s_cmd);
		close_fds(s_cmd);
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		exit_error(EXECVE, s_cmd);
	}
}

void	pipe_to_pipe_exec(t_cmd *s_cmd)
{
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count - 1][0], STDIN_FILENO) == -1)
			exit_error(DUP2, s_cmd);
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count][1], STDOUT_FILENO) == -1)
			exit_error(DUP2, s_cmd);
		if (s_cmd->here_doc)
			close_here_doc_fd(s_cmd);
		else
			close(s_cmd->fd_in);
		close_fds(s_cmd);
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		exit_error(EXECVE, s_cmd);
	}
}

void	pipe_to_fd_exec(t_cmd *s_cmd)
{
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count - 1][0], STDIN_FILENO) == -1)
			exit_error(DUP2, s_cmd);
		if (dup2(s_cmd->fd_out, STDOUT_FILENO) == -1)
			exit_error(DUP2, s_cmd);
		if (s_cmd->here_doc)
			close_here_doc_fd(s_cmd);
		else
			close(s_cmd->fd_in);
		close(s_cmd->fd_out);
		close_fds(s_cmd);
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		exit_error(EXECVE, s_cmd);
	}
}
