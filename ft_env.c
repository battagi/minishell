
#include "builtin.h"

// Function to print error for env command
void	print_env_error(char *c)
{
	write(2, "env: ", 5); // Print "env: "
	write(2, c, ft_strlen(c)); // Print the argument causing the error
	write(2, ": No such file or directory\n", 28); // Print error message
}

// Function to execute the env command
void	ft_env(t_env **env, char **arg)
{
	t_env	*tmp = *env; // Pointer to iterate through environment variables

	// Check if the "PATH" variable exists
	if (!get_env_node(env, "PATH"))
	{
		write(2, "env: No such file or directory\n", 31);
		g_glb.ex = 1; // Set error code
		return;
	}

	// If additional arguments are provided, print error
	if (arg[1])
	{
		g_glb.ex = 127; // Set error code
		print_env_error(arg[1]); // Print error message
		return;
	}

	// Iterate through the environment variables and print them
	while (tmp)
	{
		if (tmp->dx == 0 || tmp->dx == 2) // Check if the variable is valid
			printf("%s=%s\n", tmp->key, tmp->value); // Print variable
		tmp = tmp->next; // Move to the next variable
	}
	g_glb.ex = 0; // Reset error code
}