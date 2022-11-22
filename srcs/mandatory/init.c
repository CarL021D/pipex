/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:04:43 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/22 19:03:29 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_cmd_struct(t_cmd *s_cmd, char **envp)
{
	s_cmd->cmd_path = NULL;
	s_cmd->cmd_path = NULL;
	s_cmd->envp = envp;
}

void	init_fd(int id, t_cmd *s_cmd, char **av)
{
	if (FD_IN == id)
	{
		s_cmd->fd_in = open(av[1], O_RDONLY);
		if (s_cmd->fd_in == -1)
		{
			close(s_cmd->pipe_[0]);
			close(s_cmd->pipe_[1]);
			perror("Open");
			exit(EXIT_FAILURE);
		}
	}
	if (FD_OUT == id)
	{
		s_cmd->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (s_cmd->fd_out == -1)
		{
			close(s_cmd->fd_in);
			close(s_cmd->pipe_[0]);
			close(s_cmd->pipe_[1]);
			perror("Open");
			exit(EXIT_FAILURE);
		}
	}
}