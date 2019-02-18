#include "vm.h"

int main(int argc, char **argv)
{
   VmSystem system;
   MenuItem menu[MENU_SIZE];
   MenuFunction menuFunction;
   Boolean exit;

   if (argc == 1 || argc > 3)
   {
      printf("\nPlease provide the proper command line arguements.\n\n");
      return EXIT_FAILURE;
   }

   /* init system, load data and init menu */
   if (systemInit(&system) == FALSE)
   {
      printf("\nFailed to initialise system.\n\n");
      return EXIT_FAILURE;
   }
   if (loadData(&system, argv[1], argv[2]) == FALSE)
   {
      printf("\nError loading files.\n\n");
      return EXIT_FAILURE;
   }
   initMenu(menu);

   exit = FALSE;
   menuFunction = NULL;
   while (exit != TRUE)
   {
      menuFunction = getMenuChoice(menu);
      if (menuFunction == NULL)
      {
         printf("Please enter a valid option.");
         continue;
      }
      if (menuFunction == saveAndExit ||
          menuFunction == abortProgram)
      {
         exit = TRUE;
      }
      menuFunction(&system);
   }
   return EXIT_SUCCESS;
}
