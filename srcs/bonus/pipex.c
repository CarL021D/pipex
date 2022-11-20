/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 23:48:19 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/20 01:29:49 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

// Check if cmd exist inside the parent

void	var_init(t_cmd *s_cmd, int ac, char **av, char **envp)
{
	cmd_struct_init(s_cmd, ac, av, envp);
	pipe_arr_init(s_cmd);
	// if (s_cmd->here_doc)
	// 	set_here_doc(s_cmd, av);
}

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
		// fd_out_init(s_cmd, ac , av);
		pipe_to_fd_exec(s_cmd, av, ac);
	}	
	else
		pipe_to_pipe_exec(s_cmd, av);
}

void	exec_parent_process(t_cmd *s_cmd)
{
	// free_struct(s_cmd);
	close_fds(s_cmd, -1);
	// if (s_cmd->here_doc)
	// 	close_here_doc_fd(s_cmd);
	free_pipe_arr(s_cmd, s_cmd->nb_cmd - 1);
	wait_for_child_process(s_cmd);
	free(s_cmd->pid_arr);
	// waitpid(s_cmd->pid_arr[s_cmd->fork_count], NULL, 0);
}

int main(int ac, char **av, char **envp)
{
	t_cmd	s_cmd;

	exit_if_not_enough_args(ac, av);
	check_env(envp);
	// var_init(&s_cmd, ac, av, envp);
	cmd_struct_init(&s_cmd, ac, av, envp);
	pipe_arr_init(&s_cmd);
	while (s_cmd.fork_count < s_cmd.nb_cmd)
	{
		exec_child_process(&s_cmd, av, ac);
		s_cmd.fork_count++;
		s_cmd.arg_index++;
	}
	exec_parent_process(&s_cmd);
	// close_fds(&s_cmd, -1);
	// free_struct(s_cmd);
	// free_pipe_arr(&s_cmd, s_cmd.nb_cmd - 1);
	// free(s_cmd.pid_arr);
	// wait_for_child_process(&s_cmd);
}
