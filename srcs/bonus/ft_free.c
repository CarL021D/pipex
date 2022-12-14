/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:05:14 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/23 13:13:21 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_pipe_arr(t_cmd *s_cmd, int i)
{
	while (i)
	{
		free(s_cmd->pipe_arr[i - 1]);
		i--;
	}
	free(s_cmd->pipe_arr);
}

void	free_pipe_and_pid_arr(int id, t_cmd *s_cmd, int count)
{
	free(s_cmd->pid_arr);
	free_pipe_arr(s_cmd, count);
	exit_error(id, s_cmd);
}

void	free_execve_params(t_cmd *s_cmd)
{
	if (s_cmd->cmd_path != NULL)
		free(s_cmd->cmd_path);
	if (s_cmd->cmd_options != NULL)
		free_pp_arr(s_cmd->cmd_options);
}
