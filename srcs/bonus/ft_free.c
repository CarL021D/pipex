/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:05:14 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/13 23:53:16 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	free_double_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_pipe_arr(t_cmd *s_cmd, int i)
{
	while (i)
	{
		free(s_cmd->pipe_arr[i]);
		i--;
	}
	if (!s_cmd->here_doc)
		close(s_cmd->fd_in);
	free(s_cmd->pid_arr);
	exit(EXIT_FAILURE);
}

// void	free_struct(t_cmd *s_cmd)
// {
// 	if (s_cmd->cmd1_path != NULL)
// 		free(s_cmd->cmd1_path);
// 	if (s_cmd->cmd2_path != NULL)
// 		free(s_cmd->cmd2_path);
// 	if (s_cmd->cmd1_options != NULL)
// 		free_double_tab(s_cmd->cmd1_options);
// 	if (s_cmd->cmd2_options != NULL)
// 		free_double_tab(s_cmd->cmd2_options);
// 	if (s_cmd->pid_arr != NULL)
// 		free(s_cmd->pid_arr);
// }
