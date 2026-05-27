#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <stdint.h>

#include "move.h"

extern volatile _Atomic int stop_search;
void timemanager_go(Board* board, char* args);

#endif