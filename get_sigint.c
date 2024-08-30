#include "main.h"

/**
 * get_sigint - For handling the crtl + c call in prompt
 * @sig: Signal handler.
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
