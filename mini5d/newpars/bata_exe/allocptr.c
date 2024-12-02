/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:42:32 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/02 18:47:34 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	Tslash(char **path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(tmp);
		i++;
	}
}
int	size_env(t_env **env)
{
	t_env	*tmp;
	int		cnt;

	if (!env)
		return (0);
	cnt = 0;
	tmp = *env;
	while (tmp)
	{
		if (tmp->dx == 2 || tmp->dx == 0)
			cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}
char	**env_to_envp(t_env **env)
{
	char	**envp;
	t_env	*tmp;
	char	*fr;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	envp = malloc(sizeof(char *) * (size_env(env) + 1));
	tmp = *env;
	while (tmp)
	{
		if (tmp->dx == 2 || tmp->dx == 0)
		{
			fr = ft_strjoin(tmp->key, "=");
			envp[i] = ft_strjoin(fr, tmp->value);
			free(fr);
			i++;
		}
		tmp = tmp->next;
	}
	envp[i] = 0;
	return (envp);
}
t_env	*getEnvarement(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = *env;
	if (!env)
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key)) // dir !
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}
void	allocptr(t_extra *ptr, t_env **tmp, t_env **env)
{
	t_env *mis;

	*tmp = getEnvarement(env, "PATH");
	// printf("tmp = %s\n", (*tmp)->value);
	mis = *tmp;
	ptr->envp = env_to_envp(env);
	if (mis)
	{
		ptr->path = ft_split(mis->value, ':');
		Tslash(ptr->path);
	}
	ptr->pid = malloc(sizeof(int) * (ptr->size + 1));
}
