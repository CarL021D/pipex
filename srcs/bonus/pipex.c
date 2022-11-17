/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 23:48:19 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/14 00:45:01 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

// void	var_init(t_cmd *s_cmd, int ac, char **av, char **envp)
// {
// 	cmd_struct_init(s_cmd, ac, av, envp);
// 	pipe_arr_init(s_cmd);
// }

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

void	exec_parent_process(t_cmd *s_cmd)
{
	// free_struct(s_cmd);
	close_fds(s_cmd, -1);
	wait_for_child_process(s_cmd);
	// waitpid(s_cmd->pid_arr[s_cmd->fork_count], NULL, 0);
}

void	exec_child_process(t_cmd *s_cmd, char **av, int ac)
{
	s_cmd->pid_arr[s_cmd->fork_count] = fork();
	if (s_cmd->pid_arr[s_cmd->fork_count] == -1)
		exit_error(FORK, s_cmd);
	// exit_if_failed_fork(s_cmd);
	if (s_cmd->fork_count == 0)
	{
		if (s_cmd->here_doc)
			here_doc_to_pipe_exec(s_cmd, av);
		else
			fd_to_pipe_exec(s_cmd, av);
	}
	else if (s_cmd->fork_count == (s_cmd->nb_cmd - 1))
	{
		fd_out_init(s_cmd, ac , av);
		pipe_to_fd_exec(s_cmd, av, ac);
	}	
	else
		pipe_to_pipe_exec(s_cmd, av);
}

int main(int ac, char **av, char **envp)
{
	t_cmd	s_cmd;

	exit_if_not_enough_args(ac, av);
	cmd_struct_init(&s_cmd, ac, av, envp);
	pipe_arr_init(&s_cmd);
	while (s_cmd.fork_count < s_cmd.nb_cmd)
	{
		exec_child_process(&s_cmd, av, ac);
		s_cmd.fork_count++;
		s_cmd.arg_index++;
	}
	close_fds(&s_cmd, -1);
	// free_struct(s_cmd);
	wait_for_child_process(&s_cmd);
}
