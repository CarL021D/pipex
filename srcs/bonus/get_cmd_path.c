/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:19:30 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/23 14:00:29 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*cmd_env_path_line(t_cmd *s_cmd)
{
	char	*path_env;
	int		i;

	i = 0;
	while (s_cmd->envp[i])
	{
		path_env = ft_strnstr(s_cmd->envp[i], "PATH=", 5);
		if (path_env)
			return (path_env);
		i++;
	}
	return (NULL);
}

char	*get_cmd_if_no_env(char **cmd)
{
	if (access(cmd[0], F_OK | X_OK) == 0)
		return (cmd[0]);
	return (perror("Access error"), NULL);
}

char	*get_cmd_if_env(t_cmd *s_cmd, char *av, char *path_env, char **cmd)
{
	char	**split_path;
	char	*cmd_path;
	int		i;

	split_path = ft_split(path_env, ':');
	free(path_env);
	i = -1;
	while (split_path[++i])
	{
		cmd_path = join_slash_and_comd_to_path(split_path[i], cmd[0]);
		if (!cmd_path)
		{
			free_pp_arr(split_path);
			path_error(s_cmd, av, cmd, MALLOC);
			break ;
		}
		if (access(cmd_path, F_OK | X_OK) == 0 && !(cmd[0][0] == '/'))
			return (free_pp_arr(split_path),
				free_pp_arr(cmd), cmd_path);
		free(cmd_path);
	}
	free_pp_arr(split_path);
	path_error(s_cmd, av, cmd, PATH_ERROR);
	return (NULL);
}

char	*get_cmd_path(t_cmd *s_cmd, char *av)
{
	char	**cmd;
	char	*cmd_path;
	char	*path_env;

	cmd = ft_split(av, ' ');
	if (!cmd)
		return (NULL);
	path_env = cmd_env_path_line(s_cmd);
	if (!path_env)
	{
		cmd_path = get_cmd_if_no_env(cmd);
		return (cmd_path);
	}
	else
	{
		cmd_path = get_cmd_if_env(s_cmd, av, path_env, cmd);
		if (!cmd_path)
			exit(EXIT_FAILURE);
		return (cmd_path);
	}
}
