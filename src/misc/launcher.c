#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int
main(int argc, char **argv)
{
        if (argc < 2) {
                fprintf(stderr, "Usage: %s program arg1 arg1 arg3 ...\n", argv[0]);
                return 1;
        }

        const char *target = "";
#if (XX_TARGET == 32)
        target = "32";
#endif                          /* XX_TARGET */

        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%s/libflusher%s.so", getenv("ELROND_LIB"), target);
        setenv("LD_PRELOAD", buffer, 1);

        char *prog = argv[1];
        char *params[] = { NULL, NULL };        /* TODO: */
        params[0] = prog;
        execv(prog, params);

        fprintf(stderr, "ERROR: Unable to execve %s: %s\n", prog, strerror(errno));
        return 1;
}

/*
 * $Id:$
 *
 * Local Variables:
 * c-file-style: "linux"
 * indent-tabs-mode: nil
 * End:
 * vim: ai et si sw=8 ts=8
 */
