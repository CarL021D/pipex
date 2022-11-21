/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:19:30 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/21 02:50:50 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
		str[i] = (char)s1[i];
	str[i] = '/';
	i++;
	while (++j < l_s2)
		str[i++] = (char)s2[j];
	str[i] = '\0';
	return (str);
}

char	*path_str(char *full_path)
{
	char	*path;
	int		i;

	path = malloc(sizeof(char) * ft_strlen(full_path) + 1);
	if (!path)
		exit(EXIT_FAILURE);
	i = 0;
	while (full_path[i])
	{
		path[i] = full_path[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

static char	*cmd_env_path_line(char **envp)
{
	char	*path_env;
	int		i;

	i = 0;
	while (envp[i])
	{
		path_env = ft_strnstr(envp[i], "PATH=", 5);
		if (path_env)
			return (path_env);
		i++;
	}
	exit(EXIT_FAILURE);
}

char	*get_command_path(t_cmd *s_cmd, char *av, char **envp)
{
	char	**split_path;
	char	**cmd;
	char	*cmd_path;
	char	*path_env;
	int		i;

	path_env = cmd_env_path_line(envp);
	split_path = ft_split(path_env, ':');
	free(path_env);
	cmd = ft_split(av, ' ');
	i = -1;
	while (split_path[++i])
	{
		cmd_path = join_slash_and_comd_to_path(split_path[i], cmd[0]);
		if (!cmd_path)
		{
			path_error(s_cmd, av, split_path, cmd, MALLOC);
			break;
		}
		if (access(cmd_path, F_OK | X_OK) == 0 && !(cmd[0][0] == '/'))
			return (free_pp_arr(split_path), free_pp_arr(cmd), cmd_path);
		free(cmd_path);
	}
	path_error(s_cmd, av, split_path, cmd, PATH_ERROR);
	exit(EXIT_FAILURE);
	// free_pp_arr(split_path);
	// free_pp_arr(cmd);
	// free_pipe_arr(s_cmd, s_cmd->nb_cmd - 1);
	// free(s_cmd->pid_arr);
	// if (!path[i])
	// {
	// 	write(2, "zsh: command not found: ", 24);
	// 	write(2, av, ft_strlen(av));
	// 	write(2, "\n", 1);
	// }
	// else
	// 	perror("Malloc");
}
