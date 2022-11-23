/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 23:48:19 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/23 13:14:13 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wait_for_child_process(t_cmd *s_cmd)
{
	int		i;
	int		ret;

	i = 0;
	while (i < s_cmd->nb_cmd)
	{
		waitpid(s_cmd->pid_arr[i], &ret, 0);
		i++;
	}
}

void	exec_child_process(t_cmd *s_cmd, char **av, int ac)
{
	if (s_cmd->fork_count == (s_cmd->nb_cmd - 1))
		fd_out_init(s_cmd, ac, av);
	s_cmd->pid_arr[s_cmd->fork_count] = fork();
	if (s_cmd->pid_arr[s_cmd->fork_count] == -1)
		exit_error(FORK, s_cmd);
	if (s_cmd->fork_count == 0)
	{
		if (s_cmd->here_doc)
			here_doc_to_pipe_exec(s_cmd);
		else
			fd_to_pipe_exec(s_cmd);
	}
	else if (s_cmd->fork_count == (s_cmd->nb_cmd - 1))
		pipe_to_fd_exec(s_cmd);
	else
		pipe_to_pipe_exec(s_cmd);
}

void	exec_parent_process(t_cmd *s_cmd)
{
	if (s_cmd->here_doc)
		close_here_doc_fd(s_cmd);
	else
		close(s_cmd->fd_in);
	if (s_cmd->fd_out)
		close(s_cmd->fd_out);
	close_fds(s_cmd);
	free_pipe_arr(s_cmd, s_cmd->nb_cmd - 1);
	wait_for_child_process(s_cmd);
	free(s_cmd->pid_arr);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	s_cmd;

	exit_if_not_enough_args(ac, av);
	cmd_struct_init(&s_cmd, ac, av, envp);
	pipe_arr_init(&s_cmd);
	if (s_cmd.here_doc)
		set_here_doc(&s_cmd, av);
	else
		fd_in_init(&s_cmd, av);
	while (s_cmd.fork_count < s_cmd.nb_cmd)
	{
		s_cmd.cmd_path = get_cmd_path(&s_cmd, av[s_cmd.arg_index]);
		s_cmd.cmd_options = ft_split(av[s_cmd.arg_index], ' ');
		if (s_cmd.cmd_path != NULL)
			exec_child_process(&s_cmd, av, ac);
		free_execve_params(&s_cmd);
		s_cmd.fork_count++;
		s_cmd.arg_index++;
	}
	exec_parent_process(&s_cmd);
}
