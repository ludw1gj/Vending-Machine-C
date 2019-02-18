#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

typedef enum boolean
{
   FALSE = 0,
   TRUE
} Boolean;

#define NEW_LINE_SPACE 1
#define NULL_SPACE 1
#define EQUAL 0

/**
 * This is used to compensate for the extra character spaces taken up by
 * the '\n' and '\0' when input is read through fgets().
 **/
#define EXTRA_SPACES (NEW_LINE_SPACE + NULL_SPACE)

#define EMPTY_STRING ""

/**
 * Call this function whenever you detect buffer overflow.
 **/
void readRestOfLine();

/**
 * Converts a char array representing a number to type unsigned. Returns -1 if
 * conversion failed.
 **/
int convertToInt(char *strNumber);

/**
 * Get user input from stdin.
 **/
void getInput(char *input, int max);

/**
 * Formats cents, for example 930 would return "$9.30".
 **/
char *formatRemainingCents(int totalRequiredCents, int totalGivenCents, char *str);

/**
 * Formats cents, where the total given cents is mroe thans the total requried.
 **/
char *formatChangeCents(int totalRequiredCents, int totalGivenCents, char *str);

/**
 * Gets the length of an integer.
 **/
int getIntLength(int n);

#endif
