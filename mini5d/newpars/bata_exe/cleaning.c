/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:42:40 by abattagi          #+#    #+#             */
/*   Updated: 2024/12/02 18:42:44 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
void	ft_free_wait(t_extra ptr)
{
	int i;
	int status;

	free_tab(ptr.path);
	free_tab(ptr.envp);
	closingB(ptr.tube, ptr.size);
	i = 0;
	while (i <= ptr.size)
	{
		waitpid(ptr.pid[i], &status, 0);
		if (WIFSIGNALED(status))
			g_glb.ex = 128 + WTERMSIG(status);
		else
			g_glb.ex = WEXITSTATUS(status);
		i++;
	}
	free(ptr.pid);
}