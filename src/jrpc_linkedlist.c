#include <assert.h>
#include <string.h>
#include "jrpc_linkedlist.h"

jrpc_linkedlist_node *jrpc_linkedlist_node_create(const char *id,
                                                  jrpc_callback callback) {
  assert(id != JRPC_HEAD_NODE_ID);
  jrpc_linkedlist_node *node =
      (jrpc_linkedlist_node *)PORT_CALLOC(1, sizeof(jrpc_linkedlist_node));
  assert(node != NULL);
  node->id = strdup(id);
  node->callback = callback;
  node->next = NULL;

  return node;
}

void jrpc_linkedlist_node_delete(jrpc_linkedlist_node *node) {
  PORT_FREE(node->id);
  PORT_FREE(node);
}

jrpc_linkedlist *jrpc_linkedlist_create(void) {
  jrpc_linkedlist *list =
      (jrpc_linkedlist *)PORT_CALLOC(1, sizeof(jrpc_linkedlist));
  assert(list != NULL);

  jrpc_linkedlist_node *node =
      jrpc_linkedlist_node_create(JRPC_HEAD_NODE_ID, jrpc_head_callback);

  list->head = node;
  list->tail = node;

  return list;
}

/** TODO: Employ recursive strategy for list deletion? */
void jrpc_linkedlist_delete(jrpc_linkedlist *list) {
  assert(list != NULL);
  jrpc_linkedlist_node *node, *last_node;
  node = list->head;
  while (node->next != NULL) {
    last_node = node;
    node = node->next;
    jrpc_linkedlist_node_delete(last_node);
  }
  jrpc_linkedlist_node_delete(node);
  PORT_FREE(list);
}

void jrpc_linkedlist_insert(jrpc_linkedlist *list, jrpc_linkedlist_node *item) {
  /** The callback records don't need to be sorted by ID,
   * so just add new nodes to the end of the list. */
  list->tail->next = item;
  list->tail = item;
}

int jrpc_linkedlist_remove(jrpc_linkedlist *list, const char *id) {
  assert(id != JRPC_HEAD_NODE_ID);

  /** Starting at the head node, traverse the linked list and look
   * to see if the next node in the list matches the given identifier.
   * If the IDs match, update the next pointer for the current node
   * and delete the specified member. Return -1 if node is not found.
  */
  jrpc_linkedlist_node *node = list->head;
  jrpc_linkedlist_node *to_remove;
  while (node != NULL) {
    if (!strcmp(node->next->id, id)) {
      to_remove = node->next;
      node->next = node->next->next;
      jrpc_linkedlist_node_delete(to_remove);

      return 0;
    }
  }

  /** If the function has not yet returned, the node was not found. */
  return -1;
}

jrpc_callback *jrpc_linkedlist_find(jrpc_linkedlist *list, const char *id) {
  assert(list != NULL);
  assert(id != NULL);
  jrpc_linkedlist_node *node = list->head;
  while (node != NULL) {
    node = node->next;
    if (!strcmp(node->id, id)) {
      return node->callback;
    }
  }

  return NULL;
}