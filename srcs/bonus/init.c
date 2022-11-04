#include "../../includes/pipex_bonus.h"

void	cmd_struct_init(t_cmd *s_cmd, int ac, char **av, char **envp)
{
	if (str_cmp(av[1], "here_doc"))
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
	s_cmd->envp = envp;
	s_cmd->fork_count = 0;
}

void	fd_in_init(t_cmd *s_cmd, char **av)
{
	s_cmd->fd_in = open(av[1], O_RDONLY);
	if (s_cmd->fd_in == -1)
	{
		perror("Open");
		exit(EXIT_FAILURE);
	}
}

void	fd_out_init(t_cmd *s_cmd, int ac, char **av)
{
	if (s_cmd->here_doc)
		s_cmd->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		s_cmd->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	pipe_arr_init(t_cmd *s_cmd)
{
	int		nb_pipe;
	int		i;

	nb_pipe = s_cmd->nb_cmd - 1;
	s_cmd->pipe_arr = malloc(sizeof(int *) * (nb_pipe));
	if (!s_cmd->pipe_arr)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < nb_pipe)
	{
		s_cmd->pipe_arr[i] = malloc(sizeof(int) * 2);
		if (!s_cmd->pipe_arr[i])
			free_pipe_arr(s_cmd, i);
	}
	i = -1;
	while (++i < nb_pipe)
	{
		if (pipe(s_cmd->pipe_arr[i]) == -1)
		{
			perror("Pipe");
			free_pipe_arr(s_cmd, nb_pipe);
		}
	}
}
void	set_here_doc(t_cmd *s_cmd, char **av)
{
	char	*line;

	while (1)
	{
		write(1, "heredoc >", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line || str_cmp(line, av[s_cmd->arg_index]))
			break;
		write(s_cmd->pipe_here_doc[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(s_cmd->pipe_here_doc[1]);
}