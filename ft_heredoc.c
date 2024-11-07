

// // #include "builtin.h"
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include <unistd.h>
// // #include <fcntl.h>

// // void process_heredoc(const char *delimiter, t_env *env, int input_file)
// // {
// //     char *line;
// //     int tmp_fd;
// //     char tmp_filename[] = "/tmp/heredoc.txt"; 

// //     tmp_fd = open(tmp_filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
// //     if (tmp_fd == -1)
// //     {
// //         perror("open");
// //         exit(EXIT_FAILURE);
// //     }

// //     // Optionally, print the temporary file name for debugging
// //     printf("Heredoc saved in: %s\n", tmp_filename);

// //     // Now, enter the loop where we read input until the delimiter is matched
// //     while ((line = readline("heredoc> ")) != NULL)  // Read each line from user input
// //     {
// //         if (strcmp(line, delimiter) == 0)  // Check if the input matches the delimiter
// //         {
// //             free(line);  // Free the line and break out of the loop
// //             break;
// //         }
// //         // Write the line to the temporary file
// //         write(tmp_fd, line, strlen(line));  // Write the content of the line
// //         write(tmp_fd, "\n", 1);             // Write a newline character
// //         free(line);  // Free the memory allocated by readline
// //     }

// //     // Close the temporary file after writing all lines
// //     close(tmp_fd);
// //     // Optionally, unlink the temporary file if it's no longer needed
// //     // unlink(tmp_filename);
// // }

// // static void process_heredocs(t_cmd *cmd, t_env *env)
// // {
// //     t_cmd *curr;

// //     curr = cmd;
// //     while (curr != NULL)
// //     {
// //         if (curr->type == T_DLESS)
// //         {
// //             process_heredoc(curr->args[1], env, curr->input_file);
// //         }
// //         curr = curr->next;
// //     }
// // }
// // char *ft_readline(const char *prompt) {
// //     char *line = NULL;
// //     size_t len = 0;
// //     printf("%s", prompt);
// //     getline(&line, &len, stdin);
// //     // Remove the newline character if present
// //     line[strcspn(line, "\n")] = 0;
// //     return line;
// // }

// // // Example command types
// // #define T_DLESS 1

// // int main() {
// //     t_env env;  // Your environment structure
// //     t_cmd cmd;  // Command structure for testing

// //     // Set up a command for testing
// //     cmd.type = T_DLESS;
// //     cmd.args = malloc(2 * sizeof(char*));
// //     cmd.args[0] = "heredoc"; // This can be any name
// //     cmd.args[1] = "END";     // Delimiter for the heredoc
// //     cmd.next = NULL;         // No next command for this simple test

// //     // Call the process_heredocs function
// //     process_heredocs(&cmd, &env);

// //     // Clean up
// //     free(cmd.args);

// //     return 0;
// // }
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <errno.h>
// #include "builtin.h"






// char *readline(const char *prompt) {
//     char *line = NULL;
//     size_t len = 0;
//     printf("%s", prompt);
//     getline(&line, &len, stdin);
//     line[strcspn(line, "\n")] = 0;
//     return line;
// }

// int main() {
//     t_env env;
//     t_cmd cmd;

//     cmd.type = T_DLESS;
//     cmd.args = malloc(2 * sizeof(char*));
//     cmd.args[0] = "heredoc";
//     cmd.args[1] = "END";
//     cmd.next = NULL;

//     process_heredocs(&cmd, &env);

//     free(cmd.args);
//     return 0;
// }

// void process_heredoc(const char *delimiter, t_env *env, int input_file) {
//     char *line;
//     int tmp_fd;
//     char tmp_filename[] = "/tmp/heredoc.txt";

//     tmp_fd = open(tmp_filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
//     if (tmp_fd == -1) {
//         perror("open");
//         exit(EXIT_FAILURE);
//     }

//     printf("Heredoc saved in: %s\n", tmp_filename);

//     while ((line = readline("heredoc> ")) != NULL) {
//         if (strcmp(line, delimiter) == 0) {
//             free(line);
//             break;
//         }
//         write(tmp_fd, line, strlen(line));
//         write(tmp_fd, "\n", 1);
//         free(line);
//     }

//     close(tmp_fd);
// }

// static void process_heredocs(t_cmd *cmd, t_env *env) {
//     t_cmd *curr;

//     curr = cmd;
//     while (curr != NULL) {
//         if (curr->type == T_DLESS) {
//             process_heredoc(curr->args[1], env, curr->input_file);
//         }
//         curr = curr->next;
//     }
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

typedef struct s_env {
    char **variables;  // Array of environment variables
    int var_count;     // Count of variables
} t_env;

typedef struct s_cmd {
    int type;              // Command type, e.g., T_DLESS
    char **args;          // Arguments for the command
    struct s_cmd *next;   // Pointer to the next command
} t_cmd;

void process_heredoc(const char *delimiter, t_env *env);
static void process_heredocs(t_cmd *cmd, t_env *env);
char *readline(const char *prompt);

#define T_DLESS 1

int main() {
    t_env env;
    t_cmd cmd;

    // Initialize environment
    env.variables = NULL;
    env.var_count = 0;

    // Set up a command for testing
    cmd.type = T_DLESS;
    cmd.args = malloc(2 * sizeof(char*));
    if (!cmd.args) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    cmd.args[0] = "heredoc"; // Placeholder for command name
    cmd.args[1] = "END";     // Delimiter for the heredoc
    cmd.next = NULL;         // No next command for this simple test

    // Call the process_heredocs function
    process_heredocs(&cmd, &env);

    free(cmd.args);
    return 0;
}

void process_heredoc(const char *delimiter, t_env *env) {
    char *line;
    int tmp_fd;
    char tmp_filename[] = "/tmp/heredoc.txt";

    tmp_fd = open(tmp_filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (tmp_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Heredoc saved in: %s\n", tmp_filename);
    while (1) {
        line = readline("heredoc> ");
        if (!line) {
            free(line);
            break; // Handle EOF or read errors
        }
        if (strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        write(tmp_fd, line, strlen(line));
        write(tmp_fd, "\n", 1);
        free(line);
    }

    close(tmp_fd);

    // Redirect stdin to read from the heredoc file
    tmp_fd = open(tmp_filename, O_RDONLY);
    if (tmp_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (dup2(tmp_fd, STDIN_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(tmp_fd);
    // Optionally, unlink the temporary file after use
    // unlink(tmp_filename);
}

static void process_heredocs(t_cmd *cmd, t_env *env) {
    t_cmd *curr = cmd;
    while (curr != NULL) {
        if (curr->type == T_DLESS) {
            process_heredoc(curr->args[1], env);
        }
        curr = curr->next;
    }
}

// Simulated readline function
char *readline(const char *prompt) {
    char *line = NULL;
    size_t len = 0;
    printf("%s", prompt);
    getline(&line, &len, stdin);
    line[strcspn(line, "\n")] = 0;
    return line;
}