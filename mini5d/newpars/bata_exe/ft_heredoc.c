#include "../minishell.h"
void ft_error(char *message, int exit_code, int f)
{
	g_status = exit_code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	if (f == 0)
		exit(g_status);
}

static int write_to_file(char *limiter_newline, int fd, t_env *env, int x)
{
	char *line;

	while (1)
	{
		write(1, "--> ", 4);
		line = get_next_line(0);
		if (!line)
		{
			free(limiter_newline);
			break;
		}
		if (ft_strncmp(line, limiter_newline, ft_strlen(limiter_newline)) == 0)
		{
			free(line);
			free(limiter_newline);
			break;
		}
		write(fd, "\n", 1);
		free(line);
	}
	return (fd);
}

int handle_here_doc(char *limiter, t_env *env, int x)
{
	int fd;
	pid_t pid;

	fd = -1;
	pid = fork();
	fd = open("/tmp/heredocx", O_RDWR | O_CREAT | O_TRUNC, 0774);
	if (fd == -1)
		ft_error("open", 1, 0);
	if (pid == 0)
		write_to_heredoc_file(fd, limiter, env, x);
	else
		waitpid(pid, &g_status, 0);
	return (fd);
}

void get_herdoc(t_cmd **p_cmd, t_env *env, int x)
{
	t_cmd *tmp;
	t_in *in;

	tmp = *p_cmd;
	tmp->fd = -1;
	while (tmp)
	{
		in = tmp->in;
		tmp->fd = -1;
		while (in)
		{
			if (in->type == H_IN)
				tmp->fd = handle_here_doc(in->input, env, x);
			in = in->next;
		}
		tmp = tmp->next;
	}
}
