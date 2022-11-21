#include "../includes/pipex.h"

void	init_cmd_struct(t_cmd *s_cmd)
{
	s_cmd->cmd_path = NULL;
	s_cmd->cmd_path = NULL;
}

void	init_fd(int id, t_cmd *s_cmd, char **av)
{
	if (FD_IN == id)
	{
		s_cmd->fd_in = open(av[1], O_RDONLY);
		if (s_cmd->fd_in == -1)
		{
			perror("Open");
			exit(EXIT_FAILURE);
		}
	}
	if (FD_OUT == id)
	{
		s_cmd->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (s_cmd->fd_in == -1)
		{
			perror("Open");
			exit(EXIT_FAILURE);
		}
	}
}