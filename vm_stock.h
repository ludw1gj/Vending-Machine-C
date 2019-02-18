#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when restting stock.
 **/
#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"

/**
 * Allocates memory for a Stock with the provides Stock value and returns it.
 **/
Stock *createStock(Stock stock);

/**
 * Allocates memory for a Node with the provides Stock value and returns it.
 **/
Node *createNode(Stock data);

/**
 * Allocates memory for a List and returns it.
 **/
List *createList();

/**
 * Inserts a Node into the given List in alphabetical order.
 **/
void insertNode(List *list, Node *node);

/**
 * Frees a node from memory that contains the given Stock value.
 **/
int freeNodeByStock(List *list, Stock stock);

/**
 * Finds and returns the Stock that matches the ID given.
 **/
Stock *findStockByID(List *list, char id[ID_LEN + NULL_SPACE]);

/**
 * Gets a new Node ID value.
 **/
void getNewNodeId(List *list, char *nodeId);

#endif
