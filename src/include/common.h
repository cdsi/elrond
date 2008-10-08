#ifndef COMMON_H
#define COMMON_H 1

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif                          /* HAVE_CONFIG_H */

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif                          /* HAVE_INTTYPES_H */

#ifndef HAVE_AHEXTOI
#define ahextoi(x)	strtol(x, (char **)NULL, 16)
#endif                          /* ! HAVE_AHEXTOI */

#ifndef HAVE_ATOFF
#define atoff(x)	strtof(x, NULL)
#endif                          /* ! HAVE_ATOFF */

#endif                          /* ! COMMON_H */

/*
 * $Id:$
 *
 * Local Variables:
 * c-file-style: "linux"
 * indent-tabs-mode: nil
 * End:
 * vim: ai et si sw=8 ts=8
 */
