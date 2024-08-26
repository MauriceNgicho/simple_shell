#include "shell.h"

#define PROMPT "$ "

/**
 * print_envt - Prints current environment variables
 */
void print_envt(void)
{
	char **envt = environ;

	while (*envt)
	{
		printf("%s\n", *envt);
		envt++;
	}
}
/**
 * handle_command - Executes a command with arguments
 * @args: The arguments to the command
 *
 * Return: 0 on success, -1 on failure
 */
int handle_command(char **args)
{
	if (execvp(args[0], args) == -1)
	{
		perror("Error");
		return (-1);
	}
	return (0);
}

/**
 * argument_line - split line into arguments
 * @line: The input line to split
 * @args: Array to store the split arguments
 */
void argument_line(char *line, char **args)
{
	int i = 0;

	args[i] = strtok(line, " ");
	while (args[i] != NULL)
	{
		i++;
		args[i] = strtok(NULL, " ");
	}
}
/**
 * user_input - Handles input line and executes commands
 * @line: The input linie to handle
 * @args: The array to store the split arguments
 */
void user_input(char *line, char **args)
{
	argument_line(line, args);

	if (args[0] == NULL)
		return;
	if (strcmp(args[0], "envt") == 0)
	{
		print_envt();
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(0);
	}
	else
	{
		if (fork() == 0)
		{
			if (handle_command(args) == -1)
			{
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}
}
/**
 * main - Entry point for a UNIX command line interpreter
 *
 * Return: 0 on success, -1 on failure
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *args[100];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (-1);
		}
		line[strcspn(line, "\n")] = '\0';
		user_input(line, args);
	}
	free(line);
	return (0);
}
