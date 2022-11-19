/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:19:30 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/19 22:03:09 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static char	*join_slash_and_comd_to_path(char *s1, char *s2)
{
	char		*str;
	size_t		l_s1;
	size_t		l_s2;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	l_s1 = ft_strlen((char *)s1);
	l_s2 = ft_strlen((char *)s2);
	str = malloc(sizeof(char) * (l_s1 + l_s2 + 2));
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < l_s1)
		str[i] = s1[i];
	str[i] = '/';
	i++;
	while (++j < l_s2)
		str[i++] = s2[j];
	str[i] = '\0';
	return (str);
}

char	*path_str(char *full_path)
{
	char	*path;
	int		i;

	path = malloc(sizeof(char) * ft_strlen(full_path) + 1);
	if (!path)
	{
		perror("Malloc");
		exit(EXIT_FAILURE);
		// exit_error(MALLOC, s_cmd);
	}
	i = 0;
	while (full_path[i])
	{
		path[i] = full_path[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

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
	exit(EXIT_FAILURE);
}

char	*get_command_path(t_cmd *s_cmd, char *av)
{
	char	**segmented_path;
	char	*command_path;
	char	*path_env;
	char	**cmd;
	int		i;

	path_env = cmd_env_path_line(s_cmd);
	segmented_path = ft_split(path_env, ':');
	free(path_env);
	cmd = ft_split(av, ' ');
	// if (segmented_path == NULL || cmd == NULL)
	// {
	// 	perror("Malloc");
	// 	exit(EXIT_FAILURE);
	// }
	i = 0;
	while (segmented_path[i])
	{
		command_path = join_slash_and_comd_to_path(segmented_path[i], cmd[0]);
		if (!command_path)
			break;
		if (access(command_path, F_OK | X_OK) == 0)
			return (free_double_tab(segmented_path),
				free_double_tab(cmd), command_path);
		free(command_path);
		i++;
	}
	free_double_tab(segmented_path);
	free_double_tab(cmd);
	free_pipe_arr(s_cmd, s_cmd->nb_cmd - 1);
	free(s_cmd->pid_arr);
	perror("Malloc");
	exit(EXIT_FAILURE);
}
