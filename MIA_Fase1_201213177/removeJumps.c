#include "removeJumps.h"

void RemoveJumps(char* source){
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != '\n')
      i++;
  }
  *i = 0;
}
