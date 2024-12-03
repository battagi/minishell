/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:15:11 by amezioun          #+#    #+#             */
/*   Updated: 2024/11/16 12:15:12 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pwd(void)
{
    char *cwd;
    // printf("zaaaba\n");
    cwd = getcwd(NULL, 0);
    if(cwd)
    {
        printf("%s\n", cwd);
        free(cwd);
        return 0;
    }
    else
    {
        printf("errror\n");
        return 1;
    }
}
