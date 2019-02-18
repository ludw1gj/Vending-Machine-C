#include "vm_menu.h"

/**
 * vm_menu.c handles the initialisation and management of the menu array.
 **/

/**
 * In this function you need to initialise the array of menu items
 * according to the text to be displayed for the menu. This array is
 * an array of MenuItem with text and a pointer to the function
 * that will be called.
 **/
void initMenu(MenuItem *menu)
{
   int i;

   /* menu texts */
   char text[MENU_SIZE][MENU_NAME_LEN + NULL_SPACE] = {
       "1.Display Items",
       "2.Purchase Items",
       "3.Save and Exit",
       "4.Add Item",
       "5.Remove Item",
       "6.Display Coins",
       "7.Reset Stock",
       "8.Reset Coins",
       "9.Abort Program",
   };

   /* menu functions */
   MenuFunction menuFunctions[MENU_SIZE] = {
       displayItems,
       purchaseItem,
       saveAndExit,
       addItem,
       removeItem,
       displayCoins,
       resetStock,
       resetCoins,
       abortProgram};

   for (i = 0; i < MENU_SIZE; i++)
   {
      menu[i].function = menuFunctions[i];
      strncpy(menu[i].text, text[i], MENU_NAME_LEN);
   }
}

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/
MenuFunction getMenuChoice(MenuItem *menu)
{
   char input[20];
   int i;
   int choice;

   printf("\nMain Menu:\n");
   for (i = 0; i < MENU_SIZE; i++)
   {
      printf("%s\n", menu[i].text);
      if (i == 2)
      {
         printf("Administrator-Only Menu:\n");
      }
   }
   printf("Select your option (1-9): ");
   getInput(input, 20);

   choice = atoi(input) - 1;
   if (choice > 8 || choice < 0)
   {
      return NULL;
   }
   return menu[choice].function;
}
