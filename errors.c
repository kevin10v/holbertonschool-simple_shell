#include "main.h"

/**
 * print_not_found - formaton errorin "not found" sipas kërkesës
 * @prog: argv[0] i programit
 * @cmd_no: numërimi i komandës
 * @cmd: komanda e kërkuar
 */
void print_not_found(const char *prog, int cmd_no, const char *cmd)
{
	char buf[1024];

	if (!prog)
		prog = "./hsh";
	snprintf(buf, sizeof(buf), "%s: %d: %s: not found\n", prog, cmd_no, cmd);
	write(STDERR_FILENO, buf, strlen(buf));
}
