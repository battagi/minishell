#include "../minishell.h"

void exec_builtins(t_command *cmd, t_env **env)
{
	int fd;

	if (!open_files(&fd, cmd))
		return;
	if (ft_strcmp(cmd->name, "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd->name, "cd") == 0)
		cd(cmd->args, *env);
	else if (ft_strcmp(cmd->name, "env") == 0)
		ft_enva(env, cmd->args);
	else if (ft_strcmp(cmd->name, "export") == 0)
		export(cmd->args, env);
	else if (ft_strcmp(cmd->name, "echo") == 0)
		echo(cmd->args);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		unset(cmd->args, env);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		ft_exit(cmd->args, 0);
	if (fd != -2)
	{
		dup2(fd, 1);
		close(fd);
	}
}
int **alloc_tube(int size)
{
	int **tube;
	int i;

	i = 0;
	tube = malloc(sizeof(int *) * size);
	if (!tube)
		return (NULL);
	while (i < size)
	{
		tube[i] = malloc(sizeof(int) * 2);
		if (!tube[i])
			return (NULL);
		i++;
	}
	return (tube);
}
int open_pipes(int **tube, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (pipe(tube[i]) == -1)
			return (closingB(tube, i));
		i++;
	}
	return (1);
}
int **builtins_tube(t_command **list, t_env **env, int size)
{
	int **tube;
	t_command *cmd;

	cmd = *list;
	// printf("%d %s\n", size, cmd->name);
	if (size == 0 && cmd->args && is_builting(cmd))
	{
		// printf("enter to exec built\n");
		exec_builtins(cmd, env);
		return (NULL);
	}
	tube = alloc_tube(size);
	if (!open_pipes(tube, size) || !tube)
	{

		write(2, "ERROR : open_pipe ou allocation\n", 32);
		g_glb.ex = -1;
		closingB(tube, size);
		return (NULL);
	}
	return (tube);
}
void execution(t_command **list, t_env **env)
{
	t_extra ptr;
	t_command *cmd;
	t_env *tmp;
	cmd = *list;
	ptr.i = 0;
	ptr.size = ft_size_list(*list) - 1;
	ptr.tube = builtins_tube(list, env, ptr.size);
	if (!ptr.tube)
		return;

	allocptr(&ptr, &tmp, env);
	// printf("ptr.size = %d\n ptr.path %s\n", ptr.size, ptr.path);
	while (ptr.i <= ptr.size)
	{
		ptr.pid[ptr.i] = fork();
		if (!ptr.pid[ptr.i])
			handle_child(cmd, env, ptr);
		ptr.i++;
		cmd = cmd->next;
	}
	ft_free_wait(ptr);
}