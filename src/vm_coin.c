#include "vm_coin.h"

/**
 * Implement functions here for managing coins and the
 * "cash register" contained in the VmSystem struct.
 **/

/**
 * Some example functions:
 * init coins array, insert coin, change coin count for Denomination,
 * convert Denomination to coin value, deducting coins from register, etc...
 */

Denomination convertCentsToDenomination(int cents)
{
   switch (cents)
   {
   case 1000:
      return TEN_DOLLARS;
   case 500:
      return FIVE_DOLLARS;
   case 200:
      return TWO_DOLLARS;
   case 100:
      return ONE_DOLLAR;
   case 50:
      return FIFTY_CENTS;
   case 20:
      return TWENTY_CENTS;
   case 10:
      return TEN_CENTS;
   case 5:
      return FIVE_CENTS;
   default:
      return -1;
   }
}
