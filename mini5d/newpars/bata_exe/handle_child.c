#include "../minishell.h"


void	condition_dup(t_extra ptr)
{
	if (ptr.i != ptr.size)
		dup2(ptr.tube[ptr.i][1], 1);
}
void	output_cmd(t_red *out, t_extra ptr)
{
	t_red	*tmp;
	int		fd;

	tmp = out;
	if (!out)
	{
		condition_dup(ptr);
		return ;
	}
	while (tmp)
	{
		if ((tmp->type == RED_OUT  || tmp->type == RED_APP) && assining_out(tmp,
				&fd))
		{
			if (tmp->next)
				close(fd);
			else
			{
				dup2(fd, 1);
				close(fd);
			}
		}
		else
			exit(1);
		tmp = tmp->next;
	}
}
void	assaining_in(t_red *tmp)
{
	int	fd;

	fd = open(tmp->value, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR");
		exit(1);
	}
	if (tmp->next)
		close(fd);
	else
		dup2(fd, 0);
}
void	input_cmd(t_red *in, t_extra ptr, char **cmd)
{
	t_red	*tmp;

	(void)cmd;
	tmp = in;
	if (!in)
	{
		if (ptr.i != 0)
			dup2(ptr.tube[ptr.i - 1][0], 0);
		return ;
	}
	while (tmp)
	{
		if (tmp->type == RED_IN)
			assaining_in(tmp);
		// else if (tmp->type == HERDOC && !tmp->next)
		// 	read_herdoc(cmd, tmp);
		tmp = tmp->next;
	}
}
void	handle_child(t_command *cmd, t_env **env, t_extra ptr)
{

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	input_cmd(cmd->in, ptr, cmd->args);
	output_cmd(cmd->out, ptr);
	closingB(ptr.tube, ptr.size);
	if (cmd->args)
		handle_exec(ptr.path, cmd, env, ptr.envp);
	else
		exit(0);
}