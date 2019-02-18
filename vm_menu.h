#ifndef VM_MENU_H
#define VM_MENU_H

#include "vm_options.h"

/**
 * The maximum length of a menu item's text.
 **/
#define MENU_NAME_LEN 50

#define MENU_SIZE 9

/**
 * Represents a function that can be selected from the list of
 * menu_functions - creates a new type called a menu_function.
 */
typedef void (*MenuFunction)(VmSystem *);

/**
 * Represents a menu item to be displayed and executed in the program.
 **/
typedef struct menu_item
{
   char text[MENU_NAME_LEN + NULL_SPACE];
   MenuFunction function;
} MenuItem;

/**
 * Initialises the array of menu items according to the text to be displayed 
 * for the menu. This array is an array of MenuItem with text and a pointer to 
 * the function that will be called.
 **/
void initMenu(MenuItem *menu);

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/
MenuFunction getMenuChoice(MenuItem *menu);

#endif
