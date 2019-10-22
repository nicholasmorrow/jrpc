#include <memory.h>
#include <limits.h>
#define PORT_MALLOC(size) (malloc(size))
#define PORT_CALLOC(n, size) (calloc(n, size))
#define PORT_FREE(p) (free(p))

/** TODO: Fix definition so that all error codes are negative-valued
 * and JRPC_OK = 1.
*/
typedef enum {
  JRPC_OK = INT_MIN,
  JRPC_INVALID_REQUEST,
  JRPC_ERROR
} jrpc_error_t;

typedef jrpc_error_t (*jrpc_callback)(void);

jrpc_error_t jrpc_head_callback(void) { return JRPC_OK; }