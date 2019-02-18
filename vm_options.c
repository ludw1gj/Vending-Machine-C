#include "vm_options.h"

/**
 * vm_options.c this is where you need to implement the system handling
 * functions (e.g., init, free, load, save) and the main options for
 * your program. You may however have some of the actual work done
 * in functions defined elsewhere.
 **/

/**
 * Initialise the system to a known safe state. Look at the structure
 * defined in vm_system.h.
 **/
Boolean systemInit(VmSystem *system)
{
   system = (VmSystem *)malloc(sizeof(VmSystem));
   if (system == NULL)
   {
      return FALSE;
   }
   else
   {
      return TRUE;
   }
}

/**
 * Free all memory that has been allocated. If you are struggling to
 * find all your memory leaks, compile your program with the -g flag
 * and run it through valgrind.
 **/
void systemFree(VmSystem *system)
{
   Node *previous;
   Node *current;

   /* free memory of stock and nodes */
   previous = NULL;
   current = system->itemList->head;
   while (current != NULL)
   {
      previous = current;
      current = current->next;

      free(previous->data);
      previous->data = NULL;

      free(previous);
      previous = NULL;
   }

   /* free memory of list */
   free(system->itemList);
   system->itemList = NULL;
}

/**
 * Loads the stock and coin data into the system. You will also need to assign
 * the char pointers to the stock and coin file names in the system here so
 * that the same files will be used for saving. A key part of this function is
 * validation. A substantial number of marks are allocated to this function.
 **/
Boolean loadData(
    VmSystem *system, const char *stockFileName, const char *coinsFileName)
{
   Boolean loadStockSuccess;
   Boolean loadCoinsSuccess;

   system->stockFileName = stockFileName;
   system->coinFileName = coinsFileName;

   loadStockSuccess = loadStock(system, stockFileName);
   loadCoinsSuccess = loadCoins(system, coinsFileName);

   if (loadStockSuccess == TRUE && loadCoinsSuccess == TRUE)
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }
}

/**
 * Loads the stock file data into the system.
 **/
Boolean loadStock(VmSystem *system, const char *fileName)
{
   FILE *file;
   char line[256];

   Stock stock;
   system->itemList = createList();

   file = fopen(system->stockFileName, "r");
   if (file == NULL)
   {
      return FALSE;
   }

   while (fgets(line, 256, file) != NULL)
   {
      strcpy(stock.id, strtok(line, STOCK_DELIM));
      strcpy(stock.name, strtok(NULL, STOCK_DELIM));
      strcpy(stock.desc, strtok(NULL, STOCK_DELIM));
      stock.price.dollars = convertToInt(strtok(NULL, "."));
      stock.price.cents = convertToInt(strtok(NULL, STOCK_DELIM));
      stock.onHand = convertToInt(strtok(NULL, "\n"));

      insertNode(system->itemList, createNode(stock));
   }
   return TRUE;
}

/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem *system, const char *fileName)
{
   FILE *file;
   char line[256];
   Coin coin;
   int demon;
   int counter;

   file = fopen(system->coinFileName, "r");
   if (file == NULL)
   {
      return FALSE;
   }

   counter = 0;
   while (fgets(line, 256, file) != NULL)
   {
      demon = convertToInt(strtok(line, COIN_DELIM));

      coin.count = convertToInt(strtok(NULL, "\n"));
      coin.denom = convertCentsToDenomination(demon);

      system->cashRegister[counter] = coin;
      counter++;

      if (counter == NUM_DENOMS)
      {
         break;
      }
   }
   return TRUE;
}

/**
 * Saves all the stock back to the stock file.
 **/
Boolean saveStock(VmSystem *system)
{
   Node *current;
   FILE *stockFile;

   stockFile = fopen(system->stockFileName, "w+");
   if (stockFile == NULL)
   {
      printf("Error saving to %s.\n", system->stockFileName);
      return FALSE;
   }

   current = system->itemList->head;
   while (current != NULL)
   {
      fprintf(stockFile, "%s|%s|%s|%u.%u|%u\n",
              current->data->id,
              current->data->name,
              current->data->desc,
              current->data->price.dollars,
              current->data->price.cents,
              current->data->onHand);
      current = current->next;
   }
   fclose(stockFile);
   return TRUE;
}

/**
 * Saves all the coins back to the coins file.
 **/
Boolean saveCoins(VmSystem *system)
{
   return FALSE;
}

/**
 * This option allows the user to display the items in the system.
 * This is the data loaded into the linked list in the requirement 2.
 **/
void displayItems(VmSystem *system)
{
   Node *current = system->itemList->head;

   printf("\nItems Menu\n\n");
   printf("ID    | Name               | Available | Price\n");
   printf("---------------------------------------------\n");

   while (current != NULL)
   {
      printf("%-6s| %-41s| %-5d|$ %d.%.2d\n",
             current->data->id,
             current->data->name,
             current->data->onHand,
             current->data->price.dollars,
             current->data->price.cents);
      current = current->next;
   }
}

/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem *system)
{
   Stock *stock;

   char id[ID_LEN + NULL_SPACE];
   char centsInput[20];
   char fmtCents[20];

   int totalRequiredCents;
   int totalGivenCents;
   int centsUserGave;

   printf("\nPurchase Item\n");
   printf("--------------\n");

   printf("Please enter the id of the item you wish to purchase: ");
   getInput(id, ID_LEN + NULL_SPACE);

   stock = findStockByID(system->itemList, id);
   if (stock == NULL)
   {
      printf("There is no such item.");
      return;
   }
   else if (stock->onHand == 0)
   {
      printf("There is no stock of that item remaining.");
      return;
   }

   printf("You have selected “%s  %s”. This will cost you $%u.%u.\n",
          stock->name, stock->desc, stock->price.dollars, stock->price.cents);

   printf("Please hand over the money – type in the value of each note/coin in cents.\n");
   totalRequiredCents = stock->price.dollars * 100;
   totalRequiredCents += stock->price.cents;

   printf("Press enter on a new and empty line to cancel this purchase: ");
   getInput(centsInput, 20);

   centsUserGave = convertToInt(centsInput);
   if (centsUserGave == 0 || centsUserGave == -1)
   {
      printf("Cancelled.\n");
      return;
   }
   totalGivenCents = centsUserGave;

   while (totalGivenCents < totalRequiredCents)
   {
      formatRemainingCents(totalRequiredCents, totalGivenCents, fmtCents);
      printf("You still need to give us %s: ", fmtCents);

      getInput(centsInput, 20);
      centsUserGave = convertToInt(centsInput);

      /* user enters empty line or bad input */
      if (centsUserGave == 0 || centsUserGave == -1)
      {
         printf("Cancelled. User is refunded.\n");
         return;
      }
      totalGivenCents += centsUserGave;
   }
   if (totalGivenCents == totalRequiredCents)
   {
      printf("Thank you. Here is your Meat Pie.\n");
   }
   else if (totalGivenCents > totalRequiredCents)
   {
      formatChangeCents(totalRequiredCents, totalGivenCents, fmtCents);
      printf("Thank you. Here is your Meat Pie, and your change of %s.\n",
             fmtCents);
   }
   printf("Please come back soon.\n");

   stock->onHand--;
}

/**
 * You must save all data to the data files that were provided on the command
 * line when the program loaded up, display goodbye and free the system.
 * This function implements requirement 6 of the assignment specification.
 **/
void saveAndExit(VmSystem *system)
{
   saveStock(system);
   saveCoins(system);
   printf("\nGoodbye. \n\n");
}

/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem *system)
{
   Stock stock;
   char newStockId[ID_LEN + NULL_SPACE];
   char input[20];
   char *centsTemp;

   getNewNodeId(system->itemList, newStockId);
   strcpy(stock.id, newStockId);

   printf("This new meal item will have the Item id of %s.\n", stock.id);
   printf("Enter the item name: ");
   getInput(stock.name, NAME_LEN);

   printf("Enter the item description: ");
   getInput(stock.desc, DESC_LEN);

   printf("Enter the price for this item: ");
   getInput(input, 20);

   stock.price.dollars = (int)strtol(input, &centsTemp, 10);
   stock.price.cents = atoi(++centsTemp);

   /* add stock */
   stock.onHand = DEFAULT_STOCK_LEVEL;
   insertNode(system->itemList, createNode(stock));
   printf("This item “%s –  %s” has now been added to the menu.\n", stock.name, stock.desc);
}

/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem *system)
{
   char id[ID_LEN + NULL_SPACE];
   Stock stock;

   printf("Enter the item id of the item to remove from the menu: ");
   getInput(id, ID_LEN + NULL_SPACE);

   if (findStockByID(system->itemList, id) == NULL)
   {
      printf("There is no stock by that ID. Cancelling.\n");
      return;
   }
   stock = *findStockByID(system->itemList, id);

   if (freeNodeByStock(system->itemList, stock) == 0)
   {
      printf("”%s – %s” has been removed from the system.\n", stock.name, stock.desc);
      return;
   }
   printf("There has been an error when removing the item.\n");
}

/**
 * This option will require you to display the coins from lowest to highest
 * value and the counts of coins should be correctly aligned.
 * This function implements part 4 of requirement 18 in the assignment
 * specifications.
 **/
void displayCoins(VmSystem *system)
{
   int i;
   char denoms[20][100] = {
       "10 dollar",
       "5 dollar",
       "2 dollar",
       "1 dollar",
       "50 cents",
       "20 cents",
       "10 cents",
       "5 cents",
   };

   printf("\nCoins Summary\n");
   printf("---------\n");
   printf("Denomination | Count\n\n");
   for (i = NUM_DENOMS - 1; i >= 0; i--)
   {
      printf("%-12s | %d\n", denoms[i], system->cashRegister[i].count);
   }
}

/**
 * This option will require you to iterate over every stock in the
 * list and set its onHand count to the default value specified in
 * the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem *system)
{
   Node *current;

   current = system->itemList->head;
   while (current != NULL)
   {
      current->data->onHand = DEFAULT_STOCK_LEVEL;
      current = current->next;
   }
   printf("All stock has been reset to the default level of %d",
          DEFAULT_STOCK_LEVEL);
}

/**
 * This option will require you to iterate over every coin in the coin
 * list and set its 'count' to the default value specified in the
 * startup code.
 * This requirement implements part 3 of requirement 18 in the
 * assignment specifications.
 **/
void resetCoins(VmSystem *system)
{
}

/**
 * This option will require you to display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem *system)
{
   systemFree(system);
   printf("\nGoodbye. \n\n");
}
