#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int ft_print_export(t_list *env)
{
    t_list *tmp;

    tmp = env;
    while (tmp)
    {
        ft_putstr_fd("declare -x ", 1);
        if (ft_strchr(tmp->content, '='))
        {
            write(1, tmp->content, ft_strchr(tmp->content, '=') - (char *)tmp->content + 1);
            ft_putstr_fd("\"", 1);
            ft_putstr_fd(ft_strchr(tmp->content, '=') + 1, 1);
            ft_putstr_fd("\"", 1);
        }
        else
            ft_putstr_fd(tmp->content, 1);
        ft_putstr_fd("\n", 1);
        tmp = tmp->next;
    }
    return (0);
}

static int ft_set_export(char *args, t_list *env)
{
    char *var;
    char *value;

    var = ft_substr(args, 0, ft_strchr(args, '=') - args);
    value = ft_substr(args, ft_strchr(args, '=') - args + 1, ft_strlen(args));
    ft_setenv(var, value, env);
    free(var);
    free(value);
    return (0);
}

int ft_export(char **args, t_list *env)
{
    int i;

    i = 1;
    if (!args[1])
        return (ft_print_export(env));
    while (args[i])
    {
        
        if (ft_strchr(args[i], '='))
            ft_set_export(args[i], env);
        else
            ft_setenv(args[i], NULL, env);
        i++;
    }
    return (0);
}

typedef struct s_list
{
    char *content;
    struct s_list *next;
} t_list;

int main(int argc, char **argv, char **envp)
{

    t_list *env = initialize_env(envp);

    ft_export(args, env);

    free_env(env);
    return 0;
}