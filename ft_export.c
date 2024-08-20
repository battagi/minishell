#include "builtin.h"
#include <stdlib.h>

int add_env_var(t_env **head, char *key, char *value)
{
    t_env *new;
    t_env *tmp;
    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return (0);
    new->name = key;
    new->value = value;
    new->next = NULL;
    if (!*head)
    {
        *head = new;
        return (1);
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (1);
}

void ft_create_env(t_env **head, char **env)
{
    char *name;
    char *value;
    int i = 0;
    while (env[i])
    {
        value = ft_strchr(env[i], '=') + 1;
        name = ft_strcdup(env[i], '=');
        ft_add_env(head, name, value);
        i++;
    }
}




















void ft_export(int argc, char **argv, char **env)
{
    t_env *env_list;
    ft_create_env(&env_list, env);

} 