#include "vm_stock.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 */

Stock *createStock(Stock stock)
{
   Stock *newStock;

   newStock = (Stock *)malloc(sizeof(Stock));
   memcpy(newStock, &stock, sizeof(stock));
   return newStock;
}

Node *createNode(Stock data)
{
   Node *newNode;

   newNode = (Node *)malloc(sizeof(Node));
   if (newNode == NULL)
   {
      printf("Error creating a new node.\n");
      exit(0);
   }
   newNode->data = createStock(data);
   newNode->next = NULL;

   return newNode;
}

List *createList()
{
   List *newList;

   newList = (List *)malloc(sizeof(List));
   newList->head = NULL;
   newList->size = 0;

   return newList;
}

void insertNode(List *list, Node *node)
{
   Node *current;
   Node *previous;

   current = list->head;
   previous = NULL;
   if (current == NULL)
   {
      list->head = node;
      list->size++;
      return;
   }

   while (current != NULL)
   {
      /*
      if name in current-node's name is a higher value (more descendant) then 
      node's name, then it needs to be set as node's next and previous-node's 
      next is node.
      */
      if (strcmp(current->data->name, node->data->name) > EQUAL)
      {
         if (previous != NULL)
         {
            previous->next = node;
            node->next = current;
            list->size++;
            return;
         }
         /* there is only one node in the list */
         list->head = node;
         list->head->next = current;
         list->size++;
         return;
      }
      previous = current;
      current = current->next;
   }
   /* node's name is the most descendant */
   previous->next = node;
   list->size++;
}

int freeNodeByStock(List *list, Stock stock)
{
   Node *previous;
   Node *current;

   previous = NULL;
   current = list->head;
   while (current != NULL)
   {
      if (strcmp(current->data->id, stock.id) == EQUAL)
      {
         if (previous == NULL)
         {
            list->head = current->next;
         }
         else
         {
            previous->next = current->next;
         }

         /* remove node */
         free(current->data);
         current->data = NULL;
         free(current);
         current = NULL;
         return 0;
      }
      previous = current;
      current = current->next;
   }
   return -1;
}

Stock *findStockByID(List *list, char id[ID_LEN + NULL_SPACE])
{
   Node *current;

   current = list->head;
   while (current != NULL)
   {
      if (strcmp(current->data->id, id) == 0)
      {
         return current->data;
      }
      current = current->next;
   }
   return NULL;
}

void getNewNodeId(List *list, char *nodeId)
{
   Node *current;
   char *idStr;
   char zeros[6];
   int id;
   int length;
   int highestId;

   /* find heighest id */
   idStr = NULL;
   highestId = -1;
   current = list->head;
   while (current != NULL)
   {
      /* convert id to an int */
      if (current->data->id[0] == 'I')
      {
         idStr = current->data->id + 1;
      }
      id = atoi(idStr);

      /* storing highest value */
      if (highestId < id)
      {
         highestId = id;
      }
      current = current->next;
   }

   /* build new id */
   length = getIntLength(highestId);
   switch (length)
   {
   case 1:
      sprintf(zeros, "000");
      break;
   case 2:
      sprintf(zeros, "00");
      break;
   case 3:
      sprintf(zeros, "0");
      break;
   }
   if (length < 1 || length > 3)
   {
      sprintf(nodeId, "I%d", highestId + 1);
   }
   else
   {
      sprintf(nodeId, "I%s%d", zeros, highestId + 1);
   }
}
