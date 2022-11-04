

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
}

void	fd_to_pipe_exec(t_cmd *s_cmd, char **av)
{
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		fd_in_init(s_cmd, av);
		// close(s_cmd->pipe_arr[0][0]);
		if (s_cmd->fd_in == -1)
		{
			perror("Fd");
			exit(EXIT_FAILURE);
		}
		if (dup2(s_cmd->fd_in, STDIN_FILENO) == -1)
			exit_if_failed_dup();
		close(s_cmd->fd_in);
		if (dup2(s_cmd->pipe_arr[0][1], STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		close(s_cmd->pipe_arr[0][1]);
		s_cmd->cmd_path = get_command_path(s_cmd, av[s_cmd->arg_index]);
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');

		write(2, "111\n", 4);
		
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}

void	here_doc_to_pipe_exec(t_cmd *s_cmd, char **av)
{
	exit_if_failed_fork(s_cmd);
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		set_here_doc(s_cmd, av);
		close(s_cmd->pipe_here_doc[0]);
		if (s_cmd->fd_in == -1)
		{
			perror("Fd");
			exit(EXIT_FAILURE);
		}
		if (dup2(s_cmd->pipe_here_doc[0], STDIN_FILENO) == -1)
			exit_if_failed_dup();
		close(s_cmd->fd_in);
		if (dup2(s_cmd->pipe_arr[0][1], STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		close(s_cmd->pipe_here_doc[0]);
		close(s_cmd->pipe_arr[0][1]);
		s_cmd->cmd_path = get_command_path(s_cmd, av[s_cmd->arg_index]);
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}

void	pipe_to_pipe_exec(t_cmd *s_cmd, char **av)
{
	exit_if_failed_fork(s_cmd);
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		close(s_cmd->pipe_arr[s_cmd->fork_count - 1][1]);
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count - 1][0], STDIN_FILENO) == -1)
			exit_if_failed_dup();
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count][1], STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		close(s_cmd->pipe_arr[s_cmd->fork_count - 1][0]);
		close(s_cmd->pipe_arr[s_cmd->fork_count][0]);
		close(s_cmd->pipe_arr[s_cmd->fork_count][1]);
		s_cmd->cmd_path = get_command_path(s_cmd, av[s_cmd->arg_index]);
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}

void	pipe_to_fd_exec(t_cmd *s_cmd, char **av, int ac)
{
	exit_if_failed_fork(s_cmd);
	fd_out_init(s_cmd, ac, av);
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		close(s_cmd->pipe_arr[s_cmd->fork_count - 1][1]);
		if (s_cmd->fd_out == -1)
			exit(EXIT_FAILURE);
		if (dup2(s_cmd->pipe_arr[s_cmd->fork_count - 1][0], STDIN_FILENO) == -1)
			exit_if_failed_dup();
		if (dup2(s_cmd->fd_out, STDOUT_FILENO) == -1)
			exit_if_failed_dup();
		close(s_cmd->pipe_arr[s_cmd->fork_count - 1][0]);
		close(s_cmd->fd_out);
		s_cmd->cmd_path = get_command_path(s_cmd, av[s_cmd->arg_index]);
		s_cmd->cmd_options = ft_split(av[s_cmd->arg_index], ' ');

	write(2, "333\n", 4);

		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
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

void	exec_parent_process(t_cmd *s_cmd)
{
	// close(s_cmd->fd_in);
	// close(s_cmd->fd_out);
	// close(s_cmd->pipe_[0]);
	// close(s_cmd->pipe_[1]);
	// free_struct(s_cmd);
	wait_for_child_process(s_cmd);
}

void	exec_child_process(t_cmd *s_cmd, char **av, int ac)
{
	// if (s_cmd->fork_count == (s_cmd->nb_cmd - 1))
	// 	fd_out_init(s_cmd);
	s_cmd->pid_arr[s_cmd->fork_count] = fork();
	

	if (s_cmd->fork_count == 0)
	{
		write(2, "FFF\n", 4);
		if (s_cmd->here_doc)
			here_doc_to_pipe_exec(s_cmd, av);
		else
			fd_to_pipe_exec(s_cmd, av);
	}
	else if (s_cmd->fork_count < (s_cmd->nb_cmd - 1))
		pipe_to_pipe_exec(s_cmd, av);
	else
	{
		write(2, "GGG\n", 4);
		
		pipe_to_fd_exec(s_cmd, av, ac);
	}
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
	exec_parent_process(&s_cmd);
}







// int main(int ac, char **av, char **envp)
// {
// 	t_cmd	s_cmd;

// 	exit_if_not_enough_args(ac, av);
// 	init_cmd_struct(&s_cmd, ac, av);
// 	if (pipe(s_cmd.pipe_) == -1)
// 		return (perror("Pipe"), 1);
// 	if (s_cmd.here_doc)
// 		s_cmd.fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else
// 	{
// 		s_cmd.fd_in = open(av[s_cmd.arg_index], O_RDONLY);
// 		s_cmd.fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	}

// 	s_cmd.arg_index++;
// 	while (s_cmd.fork_count < s_cmd.nb_cmd)
// 	{
// 		if (s_cmd.fork_count == 0)
// 		{
// 			s_cmd.pid_arr[s_cmd.fork_count] = fork();
// 			if (s_cmd.here_doc)
// 				here_doc_to_pipe(&s_cmd, av, envp);
// 			else
// 				fd_to_pipe(&s_cmd, av, envp);		
// 		}	
// 		else
// 		{
// 			s_cmd.pid_arr[s_cmd.fork_count] = fork();
// 			exec_process(&s_cmd, av, envp);
// 		}
// 		s_cmd.arg_index++;
// 		s_cmd.fork_count++;
// 	}
// 	exec_parent_process(&s_cmd);
// }
