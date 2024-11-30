#include"minishell.h"

void	slash_exec(char **arg, char **envp)
{
	struct stat	m;

	if (stat(arg[0], &m) == -1)
		return ;
	if (S_ISDIR(m.st_mode))
		command_not_found(arg, ": is a directory\n", 126);
	else if (access(arg[0], X_OK) == -1)
		command_not_found(arg, ": Permission denied\n", 126);
	execve(arg[0], arg, envp);
}
int	there_is_slash(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
void	handle_exec(char **path, t_command *list, t_env **env, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;

	
	if (there_is_slash(list->args[0]))
		slash_exec(list->args, envp);
	if (is_builting(list))
	{
		free_tab(envp);
		exec_builtins(list, env);
		update_exit_value(env, g_glb.ex);
		exit(g_glb.ex);
	}
	else
	{

		while (getEnvarement(env, "PATH") && path[i])
		{
			tmp = ft_strjoin(path[i], list->args[0]);
			if (execve(tmp, list->args, envp) == -1)
			{
				i++;
				free(tmp);
			}
		}
	}
	update_exit_value(env, 127);
	command_not_found(list->args, ": command not found\n", 127);
}
int	closingB(int **tube, int pos)
{
	while (pos > 0)
	{
		close(tube[pos - 1][0]);
		close(tube[pos - 1][1]);
		free(tube[pos - 1]);
		pos--;
	}
	free(tube);
	return (0);
}
int	assining_out(t_red *tmp, int *fd)
{
	if (tmp->type == RED_OUT)
		*fd = open(tmp->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (tmp->type == RED_APP)
		*fd = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		perror("ERROR");
		return (0);
	}
	return (1);
}