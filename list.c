#include <stdlib.h>
#include <limits.h>

#include "list.h"

#define NIL_KEY INT_MAX

int ListIni(list_t *l) {
  list_node_t *NILnode;

  if (l == NULL)
    return 0;

  NILnode = (list_node_t *)malloc(sizeof(list_node_t));
  if (NILnode == NULL)
    return 0;

  NILnode->next = NULL;
  NILnode->key = NIL_KEY;
  l->start = NILnode;
  return 1;
}

void ListClose(list_t *l) {
  int key;
  list_node_t *n1, *n2;

  if (l == NULL)
    return;
  n1 = l->start;
  do {
    key = n1->key;
    n2 = n1->next;
    free(n1);
    n1 = n2;
  } while (key != NIL_KEY);
}

int ListInsert(list_t *l, int key) {
  list_node_t *nBefore, *nAfter, *newNode;

  if (l == NULL)
    return 0;
  nBefore = l->start;
  nAfter = l->start;
  while (nAfter->key < key) {
    nBefore = nAfter;
    nAfter = nAfter->next;
  }
  if (nAfter->key == key)
    return -1;

  newNode = (list_node_t *)malloc(sizeof(list_node_t));
  if (newNode == NULL)
    return 0;

  newNode->key = key;
  if (nAfter == nBefore) {
    newNode->next = l->start;
    l->start = newNode;
  }
  else {
    newNode->next = nAfter;
    nBefore->next = newNode;
  }
  return 1;
}

int ListFind(list_t const* l, int key) {
  list_node_t *nBefore, *nAfter;

  if (l == NULL)
    return 0;
  nBefore = l->start;
  nAfter = l->start;
  while (nAfter->key < key) {
    nBefore = nAfter;
    nAfter = nAfter->next;
  }
  if (nAfter->key == key)
    return 1;
  return 0;
}

int ListExtract(list_t *l, int key) {
  list_node_t *nBefore, *nAfter;

  if (l == NULL)
    return 0;
  nBefore = l->start;
  nAfter = l->start;
  if (key == NIL_KEY)
    return -1;

  while (nAfter->key < key) {
    nBefore = nAfter;
    nAfter = nAfter->next;
  }

  if (nAfter->key == key) {
    nBefore->next = nAfter->next;
    if (nAfter == l->start)
      l->start = nAfter->next;
    free(nAfter);
    return 1;
  }
  return 0;
}
