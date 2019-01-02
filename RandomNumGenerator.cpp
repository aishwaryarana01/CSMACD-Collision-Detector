#include "RandomNumGenerator.h"
#include<cstdlib>

int getRandomNumberInclusive(int lowerLimit, int upperLimit)
{
    return rand() % upperLimit + lowerLimit;
}