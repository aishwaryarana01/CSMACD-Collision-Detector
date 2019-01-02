#include "CollisionDetector.h"

bool isFirstStationCollided(int Station0, int Station2, int StationS0, int StationS2)
{
    //Checks the status if collision between first station and second station
    if (Station0 < 8 && Station0 >= StationS0)
    {
        return true;
    }
    //Checks the status if collision between first station and third station
    else if (Station0 >= Station2)
    {
        return true;
    }
    //Checks the status if collision in all three stations
    else if (Station0 == StationS0 || Station0 == StationS2)
    {
        return true;
    }
    return false;
}

bool isSecondStationCollided(int Station0, int Station2, int StationS0, int StationS2, int Station0MessageLength, int Station2MessageLength, int CarrierLength)
{
    //Checks the collision between first station and second station
    if (Station0 >= StationS0 && Station0 < 8)
    {
        return true;
    }
    //Checks the collision between first station and third station
    else if (StationS2 >= Station2 && Station2 > 8)
    {
        return true;
    }
    //Checks the collision in all three stations
    else if (StationS0 == Station2 || StationS2 == Station0)
    {
        return true;
    }
    else if (Station0 - Station0MessageLength > 0)
    {
        int tempPos_S0 = Station0;
        int tempLenght_S0 = Station0MessageLength;

        while (tempLenght_S0 != 0)
        {
            tempPos_S0--;
            if (tempPos_S0 == StationS2 || tempPos_S0 == StationS0)
            {
                return true;
            }
            tempLenght_S0--;
        }
    }
    else if (Station2 + Station0MessageLength > CarrierLength)
    {
        int tempPos_S2 = Station2;
        int tempLenght_S2 = Station2MessageLength;

        while (tempLenght_S2 != 0)
        {
            tempPos_S2++;
            if (tempPos_S2 == StationS2 || tempPos_S2 == StationS0)
            {
                return true;
            }
            tempLenght_S2--;
        }
    }
    return false;
}

bool isThirdStationCollided(int Station0, int Station2, int StationS0, int StationS2)
{
    //Checks the collision between third station and second station
    if (StationS2 >= Station2 && Station2 > 8)
    {
        return true;
    }
    //Checks the collision between first station and third station
    else if (Station0 >= Station2)
    {
        return true;
    }
    //Checks the collision in all three stations
    else if (StationS0 == Station2 || StationS2 == Station2)
    {
        return true;
    }
    return false;
}