/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:05:14 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/21 01:00:23 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_pp_arr(char **tab)
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

// void	free_struct(t_cmd *s_cmd)
// {
// 	if (s_cmd->cmd1_path != NULL)
// 		free(s_cmd->cmd1_path);
// 	if (s_cmd->cmd2_path != NULL)
// 		free(s_cmd->cmd2_path);
// 	if (s_cmd->cmd1_options != NULL)
// 		free_pp_arr(s_cmd->cmd1_options);
// 	if (s_cmd->cmd2_options != NULL)
// 		free_pp_arr(s_cmd->cmd2_options);
// }
