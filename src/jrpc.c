#include "jrpc.h"
#include "jrpc_common.h"
#include "jrpc_hashmap.h"

jrpc_parser *jrpc_parser_create(void) {
  jrpc_parser *parser = (jrpc_parser *)PORT_CALLOC(1, sizeof(jrpc_parser));
  assert(parser != NULL);
  parser->hashmap = jrpc_hashmap_create();
  assert(parser->hashmap != NULL);

  return parser;
}

void jrpc_parser_delete(jrpc_parser *parser) {
  assert(parser != NULL);
  jrpc_hashmap_delete(parser->hashmap);
  PORT_FREE(parser);
}

void jrpc_register_callback(jrpc_parser *parser, const char *id,
                            jrpc_callback callback) {
  assert(parser != NULL);
  assert(id != NULL);
  assert(id != JRPC_HEAD_NODE_ID);
  assert(callback != NULL);

  jrpc_hashmap_insert(parser->hashmap, id, callback);
}

void jrpc_deregister_callback(jrpc_parser *parser, const char *id) {
  assert(parser != NULL);
  assert(id != NULL);

  jrpc_hashmap_remove(parser->hashmap, id);
}

jrpc_error_t jrpc_exec(jrpc_parser *parser, const char *request) {
  /** Validate JSON frame */
  if
    /** Extract callback ID from JSON frame */
    const char *id;

  /** Execute callback */
  jrpc_callback callback = jrpc_hashmap_find(parser->hashmap, id);
  return (*callback)();
}