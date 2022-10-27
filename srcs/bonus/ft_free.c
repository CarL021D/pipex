/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:05:14 by caboudar          #+#    #+#             */
/*   Updated: 2022/10/24 16:58:02 by caboudar         ###   ########.fr       */
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

void	free_cmd_line(t_cmd *s_cmd)
{
	free(s_cmd->cmd_path);
	free_double_tab(s_cmd->cmd_options);
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
