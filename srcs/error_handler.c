/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:17:41 by caboudar          #+#    #+#             */
/*   Updated: 2022/10/19 22:32:58 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void    exit_if_not_5_args(int ac)
{
	if (ac != 5)
	{
		write(1, "5 arguments are required\n", 26);
		exit(EXIT_FAILURE);
	}
}

void	exit_if_failed_dup()
{
		perror("Dup2");
		exit(EXIT_FAILURE);
}

void	exit_if_failed_fork(t_cmd *s_cmd, int child)
{
	if (child == 1 && s_cmd->pid1 == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
	if (child == 2 && s_cmd->pid2 == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
}