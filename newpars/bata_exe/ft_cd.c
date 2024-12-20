/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:43:04 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/03 05:13:08 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd_oldpwd(t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*ret;

	tmp = get_envarement(env, "PWD");
	tmp2 = get_envarement(env, "OLDPWD");
	if (!tmp || !tmp2)
		return ;
	if (tmp2->value)
		free(tmp2->value);
	tmp2->value = ft_strdup(tmp->value);
	ret = getcwd(NULL, 0);
	if (ret)
	{
		g_glb.ex = 0;
		free(tmp->value);
		tmp->value = ret;
	}
	else
	{
		g_glb.ex = 1;
		printf("cd: error retrieving current directory: \
		getcwd: cannot access parent directories: No such file or directory\n");
	}
}

int	cd_variable(char *var, t_env **env)
{
	t_env	*tmp;

	tmp = get_envarement(env, var);
	if (!tmp || !*tmp->value)
	{
		g_glb.ex = 1;
		write(2, "cd: ", 4);
		write(2, var, ft_strlen(var));
		write(2, " not set\n", 9);
		return (0);
	}
	if (chdir(tmp->value) == -1)
	{
		g_glb.ex = 1;
		perror("cd");
		return (0);
	}
	if (ft_strcmp(var, "OLDPWD"))
		printf("%s\n", tmp->value);
	g_glb.ex = 0;
	return (1);
}

void	ft_cd(t_env **env, char **arg)
{
	if (arg[1] == NULL || ft_strcmp(arg[1], "~"))
	{
		if (!cd_variable("HOME", env))
			return ;
	}
	else if (ft_strcmp(arg[1], "-"))
	{
		if (!cd_variable("OLDPWD", env))
			return ;
	}
	else
	{
		if (chdir(arg[1]) == -1)
		{
			g_glb.ex = 1;
			perror("cd");
			return ;
		}
	}
	change_pwd_oldpwd(env);
}
