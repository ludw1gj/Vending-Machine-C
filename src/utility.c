#include "utility.h"

/**
 * Function required to be used when clearing the buffer. It simply reads
 * each char from the buffer until the buffer is empty again. Please refer
 * to the materials on string and buffer handling in the course for more
 * information.
 **/
void readRestOfLine()
{
   int ch;
   while (ch = getc(stdin), ch != EOF && ch != '\n')
   {
   } /* Gobble each character. */

   /* Reset the error status of the stream. */
   clearerr(stdin);
}

void getInput(char *input, int max)
{
   fgets(input, max, stdin);

   /* if no trailing newline then buffer overflow */
   if (!strchr(input, '\n'))
   {
      readRestOfLine();
      return;
   }
   /* remove trailing newline */
   input[strlen(input) - 1] = '\0';
}

int convertToInt(char *strNumber)
{
   char *end;
   int result;

   if (strNumber == NULL)
   {
      return -1;
   }
   result = (int)strtol(strNumber, &end, 10);

   if (!*end)
   {
      return result;
   }
   /* error in conversion */
   return -1;
}

char *formatRemainingCents(int totalRequiredCents, int totalGivenCents, char *str)
{
   int dollars;
   int cents;

   totalRequiredCents -= totalGivenCents;
   dollars = totalRequiredCents / 100;
   cents = totalRequiredCents % 100;

   sprintf(str, "$%d.%d", dollars, cents);
   return str;
}

char *formatChangeCents(int totalRequiredCents, int totalGivenCents, char *str)
{
   int dollars;
   int cents;

   totalGivenCents -= totalRequiredCents;
   dollars = totalGivenCents / 100;
   cents = totalGivenCents % 100;

   sprintf(str, "$%d.%d", dollars, cents);
   return str;
}

int getIntLength(int n)
{
   int count = 0;

   while (n != 0)
   {
      n /= 10;
      ++count;
   }
   return count;
}
