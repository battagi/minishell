
#include "builtin.h"

// Function to check if a string represents a valid number
int	is_number(char *tab)
{
	int	i = 0; // Index for traversing the string

	// Check for optional '+' or '-' sign
	if (tab[i] == '-' || tab[i] == '+')
		i++;

	// Traverse the string to ensure all characters are digits
	while (tab[i] >= '0' && tab[i] <= '9')
		i++;

	// If we reached the end of the string, it's a valid number
	return (!tab[i]);
}

// Exit function for the shell
void	ft_exit(char **cmd)
{
	printf("exit\n"); // Print "exit" message

	// If no arguments, exit with code 0
	if (!cmd[1])
		exit(0);

	// Check if the first argument is a valid number
	if (is_number(cmd[1]))
	{
		// If no additional arguments, exit with the numeric value
		if (!cmd[2])
			exit(ft_atoi(cmd[1]));
		else
		{
			// Too many arguments provided
			write(2, "exit: too many arguments\n", 26);
			g_glb.ex = 1; // Set error code
		}
	}
	else
	{
		// Argument is not a valid number
		write(2, "exit: numeric argument required\n", 33);
		exit(255); // Exit with status 255
	}
}