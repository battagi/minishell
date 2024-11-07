

#include "builtin.h"
void	ft_pwd(t_env *env)
{
	char	*p;
	t_env	*tmp;

	tmp = env;
	p = getcwd(NULL, 0);
	if (p)
	{
		printf("%s\n", p);
		free(p);
	}
	else
	{
		while (tmp)
		{
			if (ft_cmp(tmp->key, "PWD"))
			{
				printf("%s\n", tmp->value);
				break ;
			}
			tmp = tmp->next;
		}
	}
	g_glb.ex = 0;
}