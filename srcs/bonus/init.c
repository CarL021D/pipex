/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 23:48:04 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/19 20:16:52 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	cmd_struct_init(t_cmd *s_cmd, int ac, char **av, char **envp)
{
	if (ft_strcmp(av[1], "here_doc"))
	{
		s_cmd->here_doc = 1;
		s_cmd->nb_cmd = ac - 4;
		s_cmd->arg_index = 3;

	}
	else
	{
		s_cmd->here_doc = 0;
		s_cmd->nb_cmd = ac - 3;
		s_cmd->arg_index = 2;
	}
	// s_cmd->arg_index = 2;
	s_cmd->envp = envp;
	s_cmd->fork_count = 0;
	// if (pipe(s_cmd->pipe_) == -1)
	// 	return ;
	// if (pipe(s_cmd->temp_pipe))
	// 	return ;
	s_cmd->pid_arr = malloc(sizeof(pid_t) * s_cmd->nb_cmd);
	if (!s_cmd->pid_arr)
	{
		free(s_cmd->pid_arr);
		exit_error(MALLOC, s_cmd);
		// exit(EXIT_FAILURE);
	}
}

void	fd_in_init(t_cmd *s_cmd, char **av)
{
	s_cmd->fd_in = open(av[1], O_RDONLY);
	if (s_cmd->fd_in == -1)
		exit_error(OPEN, s_cmd);
	// if (s_cmd->fd_in == -1)
	// {
	// 	perror("Open");
	// 	exit(EXIT_FAILURE);
	// }
}

void	fd_out_init(t_cmd *s_cmd, int ac, char **av)
{
	if (s_cmd->here_doc)
		s_cmd->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		s_cmd->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (s_cmd->fd_out == -1)
		exit_error(OPEN, s_cmd);
	// if (s_cmd->fd_out == -1)
	// {
	// 	perror("Open");
	// 	exit(EXIT_FAILURE);
	// }
}

void	pipe_arr_init(t_cmd *s_cmd)
{
	int		nb_pipe;
	int		i;

	nb_pipe = s_cmd->nb_cmd - 1;
	s_cmd->pipe_arr = malloc(sizeof(int *) * (nb_pipe));
	if (!s_cmd->pipe_arr)
	{
		free(s_cmd->pid_arr);
		exit_error(MALLOC, s_cmd);
	}
	i = 0;
	while (i < nb_pipe)
	{
		s_cmd->pipe_arr[i] = malloc(sizeof(int) * 2);
		if (!s_cmd->pipe_arr[i])
			free_pipe_and_pid_arr(MALLOC, s_cmd, i);
		i++;
		// if (!s_cmd->pipe_arr[i])
		// {
		// 	free(s_cmd->pid_arr);
		// 	free_pipe_arr(s_cmd, i);
		// 	exit_error(MALLOC, s_cmd);
		// }
	}
	i = 0;
	while (i < nb_pipe)
	{
		if (pipe(s_cmd->pipe_arr[i]) == -1)
			free_pipe_and_pid_arr(MALLOC, s_cmd, i);
		i++;
		// if (pipe(s_cmd->pipe_arr[i]) == -1)
		// {
		// 	free(s_cmd->pid_arr);
		// 	free_pipe_arr(s_cmd, nb_pipe);
		// 	exit_error(PIPE, s_cmd);
		// }
	}
}

void	set_here_doc(t_cmd *s_cmd, char **av)
{
	char	*line;
	char	*delimeter;


	if (pipe(s_cmd->pipe_here_doc) == -1)
	{
		exit_error(PIPE, s_cmd);
		// perror("Pipe");
		// exit(EXIT_FAILURE);
	}
	delimeter = ft_strjoin(av[2], "\n");
	line = NULL;
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strcmp(line, delimeter))
			break;
		write(s_cmd->pipe_here_doc[1], line, ft_strlen(line));
		free(line);
	}
	// free(line);
	// s_cmd->fd_in = s_cmd->pipe_here_doc[0];
	// close(s_cmd->pipe_here_doc[0]);
	// close(s_cmd->pipe_here_doc[1]);
	free(delimeter);
	s_cmd->arg_index++;
}
