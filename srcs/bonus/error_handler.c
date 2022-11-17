/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:17:41 by caboudar          #+#    #+#             */
/*   Updated: 2022/10/24 18:14:59 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

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
		if (s_cmd->fd_in == -1 || s_cmd->fd_out == -1)
			perror("Open");
	if (FORK == id) 
		if (s_cmd->pid_arr[s_cmd->fork_count] == -1)
			perror("Pipe");
	exit(EXIT_FAILURE);
}

// void	exit_if_failed_dup(void)
// {
// 	perror("Dup2");
// 	exit(EXIT_FAILURE);
// }

// void	exit_if_failed_fork(t_cmd *s_cmd)
// {
// 	if (s_cmd->pid_arr[s_cmd->fork_count] == -1)
// 	{
// 		perror("Pipe");
// 		exit(EXIT_FAILURE);
// 	}
// }
