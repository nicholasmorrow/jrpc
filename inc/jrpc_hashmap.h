#include "jrpc_linkedlist.h"

/** TODO: Optimize number of buckets based on performance in expected use
 * case.*/
#define JRPC_HASHMAP_N_BUCKETS 16

typedef struct {
  jrpc_linkedlist *hash_buckets[JRPC_HASHMAP_N_BUCKETS];
} jrpc_hashmap;

jrpc_hashmap *jrpc_hashmap_create(void);
void jrpc_hashmap_delete(jrpc_hashmap *map);
void jrpc_hashmap_insert(jrpc_hashmap *map, const char *id,
                         jrpc_callback callback_function);
void jrpc_hashmap_remove(jrpc_hashmap *map, const char *id);
jrpc_callback jrpc_hashmap_find(const char *id);
int jrpc_hashmap_hash_function(const char *id);