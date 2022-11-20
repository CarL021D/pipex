/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:17:41 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/20 01:25:24 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	exit_if_not_enough_args(int ac, char **av)
{
	if (ft_strcmp(av[1], "here_doc") && (ac < 6))
	{
			write(2, "at least 6 arguments are required\n", 34);
			exit(EXIT_FAILURE);
	}
	else if (ac < 5)
	{
		write(2, "at least 5 arguments are required\n", 34);
		exit(EXIT_FAILURE);
	}
}

void	check_env(char **envp)
{
	char	*path_env;
	int		i;

	i = 0;
	while (envp[i])
	{
		path_env = ft_strnstr(envp[i], "PATH=", 5);
		if (path_env != NULL)
			return ;
		i++;
	}
	write(2, "No environment\n", 16);
}

void	error_no_path(t_cmd *s_cmd, char *av, char **path, char **cmd, int i)
{
	free_double_tab(path);
	free_double_tab(cmd);
	free_pipe_arr(s_cmd, s_cmd->nb_cmd - 1);
	free(s_cmd->pid_arr);
	if (!path[i])
	{
		write(2, "zsh: command not found: ", 24);
		write(2, av, ft_strlen(av));
		write(2, "\n", 1);
	}
	else
		perror("Malloc");
}

void	exit_error(int id, t_cmd *s_cmd)
{
	if (MALLOC == id)
		perror("Malloc");
	if (PIPE == id)
		perror("Pipe");
	if (DUP2 == id)
		perror("Dup2");
	if (EXECVE == id)
		perror("Execve");
	if (OPEN == id)
		perror("Open");
	if (FORK == id) 
		if (s_cmd->pid_arr[s_cmd->fork_count] == -1)
			perror("Pipe");
	exit(EXIT_FAILURE);
}

// void	exit_if_failed_dup(void)
// {
// 	perror("Dup2");
// 	exit(EXIT_FAILURE);
// }

// void	exit_if_failed_fork(t_cmd *s_cmd)
// {
// 	if (s_cmd->pid_arr[s_cmd->fork_count] == -1)
// 	{
// 		perror("Pipe");
// 		exit(EXIT_FAILURE);
// 	}
// }
