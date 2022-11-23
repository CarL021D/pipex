/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:17:41 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/23 13:12:42 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_if_not_enough_args(int ac, char **av)
{
	if (ft_strcmp(av[1], "here_doc") && (ac < 6))
	{
		write(2, "at least 6 arguments are required\n", 34);
		exit(EXIT_FAILURE);
	}
	else if (ac < 5)
	{
		write(2, "at least 5 arguments are required\n", 34);
		exit(EXIT_FAILURE);
	}
}

void	path_error(t_cmd *s_cmd, char *av, char **cmd, int id)
{
	free_pp_arr(cmd);
	if (s_cmd->here_doc)
		close_here_doc_fd(s_cmd);
	else
		close(s_cmd->fd_in);
	close_fds(s_cmd);
	free_struct(s_cmd);
	if (PATH_ERROR == id)
	{
		write(2, "zsh: command not found: ", 24);
		write(2, av, ft_strlen(av));
		write(2, "\n", 1);
	}
	if (MALLOC == id)
		perror("Malloc");
}

void	exit_error(int id, t_cmd *s_cmd)
{
	if (MALLOC == id)
		perror("Malloc");
	if (PIPE == id)
		perror("Pipe");
	if (DUP2 == id)
		perror("Dup2");
	if (EXECVE == id)
		perror("Execve");
	if (OPEN == id)
		perror("Open");
	if (FORK == id)
		if (s_cmd->pid_arr[s_cmd->fork_count] == -1)
			perror("Pipe");
	exit(EXIT_FAILURE);
}
