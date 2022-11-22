/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:17:41 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/22 23:49:11 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exit_if_not_5_args(int ac)
{
	if (ac != 5)
	{
		write(2, "5 arguments are required\n", 26);
		exit(EXIT_FAILURE);
	}
}

void	exit_if_failed_fd_open(t_cmd *s_cmd, int id)
{
	if (FD_IN == id && s_cmd->fd_in == -1)
	{
		perror("Open");
		exit(EXIT_FAILURE);
	}
	if (FD_OUT == id && s_cmd->fd_out == -1)
	{
		perror("Open");
		exit(EXIT_FAILURE);
	}
}

void	exit_if_failed_dup(t_cmd *s_cmd)
{
	if (s_cmd->fd_in)
		close(s_cmd->fd_in);
	if (s_cmd->fd_out)
		close(s_cmd->fd_out);
	perror("Dup2");
	exit(EXIT_FAILURE);
}

void	exit_if_failed_fork(t_cmd *s_cmd, int child)
{
	if (child == 1 && s_cmd->pid_1 == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
	if (child == 2 && s_cmd->pid_2 == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
}

void	path_error(t_cmd *s_cmd, char *av, char **cmd, int id)
{
	free_pp_arr(cmd);
	close(s_cmd->fd_in);
	close(s_cmd->pipe_[0]);
	close(s_cmd->pipe_[1]);
	if (PATH_ERROR == id)
	{
		write(2, "zsh: command not found: ", 24);
		write(2, av, ft_strlen(av));
		write(2, "\n", 1);
	}
	if (MALLOC == id)
		perror("Malloc");
}
