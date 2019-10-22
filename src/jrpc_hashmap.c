#include "jrpc_hashmap.h"

jrpc_hashmap *jrpc_hashmap_create(void) {
  jrpc_hashmap *map = (jrpc_hashmap *)(1, sizeof(jrpc_hashmap));
  assert(map != NULL);
  for (int i = 0; i < JRPC_HASHMAP_N_BUCKETS; i++) {
    map->hash_buckets[i] = jrpc_linkedlist_create();
    assert(map->hash_buckets[i] != NULL);
  }

  return map;
}

void jrpc_hashmap_delete(jrpc_hashmap *map) {
  for (int i = 0; i < JRPC_HASHMAP_N_BUCKETS; i++) {
    jrpc_linkedlist_delete(map->hash_buckets[i]);
  }
  PORT_FREE(map);
}

void jrpc_hashmap_insert(jrpc_hashmap *map, const char *id,
                         jrpc_callback callback) {
  assert(map != NULL);
  assert(id != NULL);
  assert(id != JRPC_HEAD_NODE_ID);
  assert(callback != NULL);
  jrpc_linkedlist_node *node = jrpc_linkedlist_node_create(id, callback);
  unsigned int hash = jrpc_hashmap_hash_function(id);
  jrpc_linkedlist *list = map->hash_buckets[hash];
  jrpc_linkedlist_insert(list, node);
}

void jrpc_hashmap_remove(jrpc_hashmap *map, const char *id) {
  assert(map != NULL);
  assert(id != NULL);
  unsigned int hash = jrpc_hashmap_hash_function(id);
  jrpc_linkedlist *bucket = map->hash_buckets[hash];
  jrpc_linkedlist_remove(bucket, id);
}

jrpc_callback jrpc_hashmap_find(jrpc_hashmap *map, const char *id) {
  jrpc_callback callback;
  unsigned int hash = jrpc_hashmap_hash_function(id);
  jrpc_linkedlist *bucket = map->hash_buckets[hash];
  callback = jrpc_linkedlist_find(bucket, id);
  return callback;
}

unsigned int jrpc_hashmap_hash_function(const char *id) {
  /** TODO: Analyze performance to see if there is significant
   * benefit to using a less trivial hash algorithm.
  */
  unsigned int sum;
  for (int i = 0; i < strlen(id); i++) {
    sum += (int)id[i];
  }
  return sum % JRPC_HASHMAP_N_BUCKETS;
}