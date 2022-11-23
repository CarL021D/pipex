/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:24:25 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/23 13:12:34 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_here_doc_fd(t_cmd *s_cmd)
{
	close(s_cmd->pipe_here_doc[0]);
	close(s_cmd->pipe_here_doc[1]);
}

void	close_fds(t_cmd *s_cmd)
{
	int		i;

	i = 0;
	while (i < (s_cmd->nb_cmd - 1))
	{
		close(s_cmd->pipe_arr[i][0]);
		close(s_cmd->pipe_arr[i][1]);
		i++;
	}
}
