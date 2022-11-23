/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:10:14 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/23 13:48:54 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	free_struct(t_cmd *s_cmd)
{
	free(s_cmd->pid_arr);
	free_pipe_arr(s_cmd, (s_cmd->nb_cmd - 1));
}

void	gnl_cleaner(char *stash, char *line)
{
	free(stash);
	free(line);
}
