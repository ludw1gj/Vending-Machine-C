#ifndef VM_COIN_H
#define VM_COIN_H

#include "vm_system.h"

/**
 * The default coin level used when resetting values.
 **/
#define DEFAULT_COIN_COUNT 20

#define COIN_DELIM ","

/**
 * Takes cents as input and returns the proper Denomination.
 **/
Denomination convertCentsToDenomination(int cents);

#endif
