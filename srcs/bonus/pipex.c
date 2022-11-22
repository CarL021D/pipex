/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 23:48:19 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/22 19:40:54 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

// Check if cmd exist inside the parent

// static void	ft_putnbr_fd(int n, int fd)
// {
// 	long int	l;

// 	l = n;
// 	if (l < 0)
// 	{
// 		write(fd, "-", 1);
// 		l = -l;
// 	}
// 	if (l >= 10)
// 	{
// 		ft_putnbr_fd(l / 10, fd);
// 		ft_putnbr_fd(l % 10, fd);
// 	}
// 	else
// 	{
// 		l += 48;
// 		write(fd, &l, 1);
// 	}
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


// void	exec_child_process(t_cmd *s_cmd, char **av)
void	exec_child_process(t_cmd *s_cmd, char **av, int ac)
{
	if (s_cmd->fork_count == (s_cmd->nb_cmd - 1))
		fd_out_init(s_cmd, ac, av);
		// init_fd(FD_OUT, s_cmd, av, ac);
	s_cmd->pid_arr[s_cmd->fork_count] = fork();
	if (s_cmd->pid_arr[s_cmd->fork_count] == -1)
		exit_error(FORK, s_cmd);
	// exit_if_failed_fork(s_cmd);
	if (s_cmd->fork_count == 0)
	{
		if (s_cmd->here_doc)
			here_doc_to_pipe_exec(s_cmd);
		else
			fd_to_pipe_exec(s_cmd);
	}
	else if (s_cmd->fork_count == (s_cmd->nb_cmd - 1))
		pipe_to_fd_exec(s_cmd);
		// init_fd(FD_OUT, s_cmd, av, ac);
		// fd_out_init(s_cmd, ac , av);
		// pipe_to_fd_exec(s_cmd, av ,ac);
	else
		pipe_to_pipe_exec(s_cmd);
}

void	exec_parent_process(t_cmd *s_cmd)
{
	// // free_struct(s_cmd);
	if (s_cmd->here_doc)
		close_here_doc_fd(s_cmd);
	else
		close(s_cmd->fd_in);
	// if (s_cmd->cmd_path)
	if (s_cmd->fd_out)
		close(s_cmd->fd_out);
	close_fds(s_cmd);
	// if (s_cmd->here_doc)
	// 	close_here_doc_fd(s_cmd);
	free_pipe_arr(s_cmd, s_cmd->nb_cmd - 1);
	wait_for_child_process(s_cmd);
	free(s_cmd->pid_arr);

	// waitpid(s_cmd->pid_arr[s_cmd->fork_count], NULL, 0);
}

void	free_execve_params(t_cmd *s_cmd)
{
	if (s_cmd->cmd_path != NULL)
		free(s_cmd->cmd_path);
	if (s_cmd->cmd_options != NULL)
		free_pp_arr(s_cmd->cmd_options);
}

// void	init_fd(int id, t_cmd *s_cmd, char **av, int ac)
// {
// 	if (FD_IN == id)
// 	{
// 		s_cmd->fd_in = open(av[1], O_RDONLY);
// 		if (s_cmd->fd_in == -1)
// 		{
// 			close_fds(s_cmd);
// 			free_struct(s_cmd);
// 			exit_error(OPEN, s_cmd);
// 		}
// 	}
// 	if (FD_OUT == id)
// 	{
// 		if (s_cmd->here_doc)
// 			s_cmd->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		else
// 			s_cmd->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (s_cmd->fd_out == -1)
// 		{
// 			if (s_cmd->here_doc)
// 				close_here_doc_fd(s_cmd);
// 			else
// 				close(s_cmd->fd_in);
// 			close_fds(s_cmd);
// 			free_struct(s_cmd);
// 			free_execve_params(s_cmd);
// 			exit_error(OPEN, s_cmd);
// 		}
// 	}
// }


// static void	check_path(t_cmd *s_cmd, char **av);
// {
	


	
// }



int main(int ac, char **av, char **envp)
{
	t_cmd	s_cmd;

	exit_if_not_enough_args(ac, av);
	// check_env(envp);
	cmd_struct_init(&s_cmd, ac, av, envp);
	pipe_arr_init(&s_cmd);
	if (s_cmd.here_doc)
		set_here_doc(&s_cmd, av);
	else
		fd_in_init(&s_cmd, av);
		// init_fd(FD_IN, &s_cmd, av, ac);
	while (s_cmd.fork_count < s_cmd.nb_cmd)
	{
		// check_path(&s_cmd, av);
		s_cmd.cmd_path = get_cmd_path(&s_cmd, av[s_cmd.arg_index]);
		s_cmd.cmd_options = ft_split(av[s_cmd.arg_index], ' ');
		if (s_cmd.cmd_path != NULL)
			exec_child_process(&s_cmd, av, ac);
		free_execve_params(&s_cmd);
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
