
#include "builtin.h"

// Function to update PWD and OLDPWD environment variables
void	change_pwd_oldpwd(t_env **env)
{
	t_env	*tmp = get_env_node(env, "PWD"); // Get current working directory
	t_env	*tmp2 = get_env_node(env, "OLDPWD"); // Get previous working directory
	char	*ret; // Variable to hold the result of getcwd

	if (!tmp || !tmp2) // If either variable is not found, return
		return;

	if (tmp2->value) // If OLDPWD has a value, free it
		free(tmp2->value);
	tmp2->value = ft_strdup(tmp->value); // Set OLDPWD to current PWD

	ret = getcwd(NULL, 0); // Get the current working directory
	if (ret)
	{
		g_glb.ex = 0; // Reset error code
		free(tmp->value); // Free previous PWD value
		tmp->value = ret; // Update PWD with the new directory
	}
	else
	{
		g_glb.ex = 1; // Set error code if getcwd fails
		printf("cd: error retrieving current directory: \
		getcwd: cannot access parent directories: No such file or directory\n");
	}
}

// Function to change directory based on environment variable
int	cd_var(char *var, t_env **env)
{
	t_env	*tmp = get_env_node(env, var); // Get the environment variable

	if (!tmp || !*tmp->value) // If variable not found or empty
	{
		g_glb.ex = 1; // Set error code
		write(2, "cd: ", 4);
		write(2, var, ft_strlen(var)); // Print variable name
		write(2, " not set\n", 9); // Print error message
		return (0);
	}

	if (chdir(tmp->value) == -1) // Change to the directory
	{
		g_glb.ex = 1; // Set error code if chdir fails
		perror("cd"); // Print error message
		return (0);
	}

	if (ft_cmp(var, "OLDPWD")) // If changing to OLDPWD, print it
		printf("%s\n", tmp->value);
	g_glb.ex = 0; // Reset error code
	return (1); // Successful change
}

// Main cd function
void	ft_cd(t_env **env, char **arg)
{
	// Check for tilde or no argument
	if (arg[1] == NULL || ft_cmp(arg[1], "~"))
	{
		if (!cd_var("HOME", env)) // Change to HOME directory
			return;
	}
	else if (ft_cmp(arg[1], "-")) // Check for OLDPWD
	{
		if (!cd_var("OLDPWD", env)) // Change to OLDPWD
			return;
	}
	else
	{
		if (chdir(arg[1]) == -1) // Change to specified directory
		{
			g_glb.ex = 1; // Set error code if chdir fails
			perror("cd"); // Print error message
			return;
		}
	}
	change_pwd_oldpwd(env); // Update PWD and OLDPWD
}