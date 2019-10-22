#include "jrpc_common.h"

#define JRPC_HEAD_NODE_ID "jrpc_head"

/** Singly-linked list*/

typedef struct {
  const char *id;
  jrpc_callback callback;
  jrpc_linkedlist_node *next;
} jrpc_linkedlist_node;

typedef struct {
  jrpc_linkedlist_node *head;
  jrpc_linkedlist_node *tail;
} jrpc_linkedlist;

jrpc_linkedlist_node *jrpc_linkedlist_node_create(void);
void jrpc_linkedlist_node_delete(jrpc_linkedlist_node *node);

jrpc_linkedlist *jrpc_linkedlist_create(void);
void jrpc_linkedlist_delete(jrpc_linkedlist *list);
void jrpc_linkedlist_insert(jrpc_linkedlist *list, jrpc_linkedlist_node *item);
int jrpc_linkedlist_remove(jrpc_linkedlist *list, const char *id);
jrpc_callback *jrpc_linkedlist_find(jrpc_linkedlist *list, const char *id);
