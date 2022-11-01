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

void	exit_if_less_than_5_args(int ac)
{
	if (ac < 5)
	{
		write(1, "at least 5 arguments are required\n", 34);
		exit(EXIT_FAILURE);
	}
}

void	exit_if_failed_dup(void)
{
	perror("Dup2");
	exit(EXIT_FAILURE);
}

void	exit_if_failed_fork(t_cmd *s_cmd)
{
	if (s_cmd->pid_arr[s_cmd->fork_count] == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
}
