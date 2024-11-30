#include "../minishell.h"




int	condition_name(char *c)
{
	if (!(*c >= 'a' && *c <= 'z') && !(*c >= 'A' && *c <= 'Z') && *c != '_')
		return (0);
	while (*c && *c != '=')
	{
		if (!(*c >= 'a' && *c <= 'z') \
			&& !(*c >= 'A' && *c <= 'Z') && !(*c >= '0' && *c <= '9') \
			&& *c != '_')
			return (0);
		c++;
	}
	return (1);
}
void	free_env(t_env *node)
{
	free(node->key);
	free(node->value);
}

void	env_del(t_env *lst)
{
	free_env(lst);
	free(lst);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
void	command_not_found(char **arg, char *mes, int ret)
{
	write(2, arg[0], ft_strlen(arg[0]));
	write(2, mes, ft_strlen(mes));
	exit(ret);
}

