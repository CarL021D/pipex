#include "../../includes/pipex_bonus.h"

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
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
	waitpid(s_cmd->pid_arr[s_cmd->fork_count], NULL, 0);
}

void	here_doc_to_pipe_exec(t_cmd *s_cmd, char **av)
{
	if (s_cmd->pid_arr[s_cmd->fork_count] == 0)
	{
		// close(s_cmd->pipe_here_doc[0]);
		if (s_cmd->fd_in == -1)
		{
			perror("Fd");
			exit(EXIT_FAILURE);
		}
		if (dup2(s_cmd->pipe_here_doc[0], STDIN_FILENO) == -1)
		{
			write(2, "errorP\n", 7);
			exit_if_failed_dup();
		}
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
	waitpid(s_cmd->pid_arr[s_cmd->fork_count], NULL, 0);
}

void	pipe_to_pipe_exec(t_cmd *s_cmd, char **av)
{
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
		execve(s_cmd->cmd_path, s_cmd->cmd_options, s_cmd->envp);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
}