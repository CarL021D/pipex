

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipex.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/10/05 08:03:11 by caboudar          #+#    #+#             */
// /*   Updated: 2022/10/20 17:09:25 by caboudar         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	var_init(t_cmd *s_cmd, int ac, char **av, char **envp)
{
	cmd_struct_init(s_cmd, ac, av, envp);
	pipe_arr_init(s_cmd);
	if (s_cmd->here_doc)
		set_here_doc(s_cmd, av);
}

void	wait_for_child_process(t_cmd *s_cmd)
{
	int		i;

	i = 0;
	while (i < s_cmd->fork_count)
	{
		waitpid(s_cmd->pid_arr[i], NULL, 0);
		i++;
	}
}

// void	exec_parent_process(t_cmd *s_cmd)
// {
// 	// close(s_cmd->fd_in);
// 	// close(s_cmd->fd_out);
// 	// close(s_cmd->pipe_[0]);
// 	// close(s_cmd->pipe_[1]);
// 	// free_struct(s_cmd);
// 	// wait_for_child_process(s_cmd);
// 	// waitpid(s_cmd->pid_arr[s_cmd->fork_count], NULL, 0);
// }

void	exec_child_process(t_cmd *s_cmd, char **av, int ac)
{
	s_cmd->pid_arr[s_cmd->fork_count] = fork();
	exit_if_failed_fork(s_cmd);
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
	var_init(&s_cmd, ac, av, envp);
	while (s_cmd.fork_count < s_cmd.nb_cmd)
	{
		exec_child_process(&s_cmd, av, ac);
		// waitpid(s_cmd.pid_arr[s_cmd.fork_count], NULL, 0);
		s_cmd.fork_count++;
		s_cmd.arg_index++;
	}
	// waitpid(s_cmd.pid_arr[0], NULL, 0);
	// exec_parent_process(&s_cmd);
}
