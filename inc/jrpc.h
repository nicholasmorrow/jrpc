#include "jrpc_hashmap.h"

typedef struct { jrpc_hashmap *hashmap; } jrpc_parser;

jrpc_parser *jrpc_parser_create(void);
void jrpc_parser_delete(jrpc_parser *parser);
void jrpc_register_callback(jrpc_parser *parser, const char *id,
                            jrpc_callback callback);
void jrpc_deregister_callback(jrpc_parser *parser, const char *id);
jrpc_error_t jrpc_request_validate(const char *request);
jrpc_error_t jrpc_exec(jrpc_parser *parser, const char *request);