#include<cstdlib>
#include<ctime>
#include<iostream>

#include "CollisionDetector.h"
#include "RandomNumGenerator.h"

#define PROBABILITY_REQUIRED_TO_SEND_MSG 0.9

using namespace std;

int getLatency(int ticks, int successCount)
{
    return successCount != 0 ? (ticks / successCount) : -1;
}

int main()
{
    int CarrierLength = getRandomNumberInclusive(1, 50);

    int Station0 = 0, Station1, Station2 = CarrierLength,
        StationS0 = 8, StationS1 = 8, StationS2 = 8,
        Station0Dest = 0, Station1Dest = 0, Station2Dest = 0,
        NumDelayCountS0 = 0, NumDelayCountS1 = 0, NumDelayCountS2 = 0,
        NumDelayTicksS0 = 0, NumDelayTicksS1 = 0, NumDelayTicksS2 = 0,
        Station0MessageLength = 0, Station1MessageLength = 0, Station2MessageLength = 0,
        Station0SucessfulTransmission = 0, Station1SucessfulTransmission = 0, Station2SucessfulTransmission = 0,
        Station0ticks = 0, Station1ticks = 0, Station2ticks = 0,
        TotalNoTicksS0 = 0, TotalNoTicksS1 = 0, TotalNoTicksS2 = 0;

    bool    CollisionS0 = false, CollisionS1 = false, CollisionS2 = false,
            DelayS0 = false, DelayS1 = false, DelayS2 = false,
            S0Transmission =false, S1Transmission = false, S2Transmission = false,
            S0LastMessage = false, S1LastMessage=false, S2LastMessage=false;

    float probability1, probability2, probability3;

    srand(time(0));

    //No. of ticks
    for (int i = 0; i < 1500; i++)
    {
        //No of station
        for (int j = 0; j < 3; j++)
        {
            //J loops checks for station i.e checks for station 1
            if (j == 0)
            {
                CollisionS0 = isFirstStationCollided(Station0, Station2, StationS0, StationS2);

                //checks if the station is under collision delay time
                if (DelayS0)
                {
                    CollisionS0 = false;
                    //checks if collision time is complete
                    if (NumDelayCountS0 == NumDelayTicksS0)
                    {
                        DelayS0 = false;
                        NumDelayCountS0 = 0;
                    }
                    //checks if collision time is not complete
                    if (NumDelayCountS0 < NumDelayTicksS0)
                    {
                        //then increment
                        NumDelayCountS0++;
                    }
                }
                else
                {
                    if (!CollisionS0 && !CollisionS1 && !CollisionS2)
                    {
                        //checks is there is transmission going on currently
                        if (!S0Transmission)
                        {
                            if (!S0LastMessage)
                            {
                                Station0ticks = 0;
                            }

                            //assigning probability
                            probability1 = (float) rand() / (float) RAND_MAX;
                            //check the Station 0 destination
                            Station0Dest = getRandomNumberInclusive(1, 2);
                            Station0MessageLength = getRandomNumberInclusive(1, 3);

                            if (probability1 > PROBABILITY_REQUIRED_TO_SEND_MSG)
                            {
                                S0Transmission = true;
                                Station0++;
                                Station0ticks++;
                            }
                        }
                        else
                        {
                            Station0++;
                            Station0ticks++;
                        }
                    }
                    else
                    {
                        S0LastMessage = true;
                        S0Transmission = false;
                        Station0 = 0;
                        NumDelayTicksS0 = getRandomNumberInclusive(1, 24);
                        DelayS0 = true;
                        NumDelayCountS0 = 1;
                    }
                }
                //Message successfully reached from Station S0 to Station S1
                if (Station0Dest == 1 && Station0 == 8)
                {
                    TotalNoTicksS0 = TotalNoTicksS0 + Station0ticks;
                    Station0SucessfulTransmission++;
                    S0LastMessage = false;
                    Station0ticks = 0;
                    S0Transmission = false;
                    Station0 = 0;
                    Station0Dest = 0;
                }
                //Message successfully reached from Station S0 to Station S2
                if (Station0Dest == 2 && Station0 == CarrierLength)
                {
                    TotalNoTicksS0 = TotalNoTicksS0 + Station0ticks;
                    Station0SucessfulTransmission++;
                    S0LastMessage = false;
                    Station0ticks = 0;
                    S0Transmission = false;
                    Station0 = 0;
                    Station0Dest = 0;
                }
            }
            //Checks for second station
            else if (j == 1)
            {
                CollisionS1 = isSecondStationCollided(Station0, Station2, StationS0, StationS2, Station0MessageLength, Station2MessageLength, CarrierLength);

                //checks if the station is under collision delay time
                if (DelayS1)
                {
                    CollisionS1 = false;
                    //checks if collision time is complete
                    if (NumDelayCountS1 == NumDelayTicksS1)
                    {
                        DelayS1 = false;
                        NumDelayCountS1 = 0;
                    }
                    //checks if collision time is not complete
                    if (NumDelayCountS1 < NumDelayTicksS1)
                    {
                        NumDelayCountS1++;
                    }
                }
                else
                {
                    if (!CollisionS0 && !CollisionS1 && !CollisionS2)
                    {
                        //checks is there is transmission going on currently
                        if (!S1Transmission)
                        {
                            if (!S1LastMessage)
                            {
                                Station1ticks = 0;
                            }

                            probability2 = (float) rand() / (float) RAND_MAX;
                            Station1Dest  = getRandomNumberInclusive(1, 2);

                            if (probability2 > PROBABILITY_REQUIRED_TO_SEND_MSG)
                            {
                                S1Transmission = true;
                                StationS0--;
                                StationS2++;
                                Station1ticks++;
                            }
                        }
                        else
                        {
                            StationS0--;
                            StationS2++;
                            Station1ticks++;
                        }
                    }
                    else
                    {
                        S1LastMessage = true;
                        S1Transmission = false;
                        StationS0 = 8;
                        StationS2 = 8;
                        NumDelayTicksS1 = getRandomNumberInclusive(1, 24);
                        DelayS1 = true;
                        NumDelayCountS1 = 1;
                    }
                }
                if (Station1Dest  == 1 && StationS0 == 0)
                {
                    TotalNoTicksS1 = TotalNoTicksS1 + Station1ticks;
                    Station1SucessfulTransmission++;
                    S1LastMessage = false;
                    Station1ticks = 0;
                    S1Transmission = false;
                    StationS0 = 8;
                    Station1Dest  = 0;
                }
                if (Station1Dest  == 2 && StationS2 == CarrierLength)
                {
                    TotalNoTicksS1 = TotalNoTicksS1 + Station1ticks;
                    Station1SucessfulTransmission++;
                    S1LastMessage = false;
                    Station1ticks = 0;
                    S1Transmission = false;
                    StationS2 = 8;
                    Station1Dest  = 0;
                }
            }
            //checks for third Station
            else if (j == 2)
            {
                CollisionS2 = isThirdStationCollided(Station0, Station2, StationS0, StationS2);

                //checks if the station is under collision delay time
                if (DelayS2)
                {
                    CollisionS2 = false;
                    //checks if collision time is complete
                    if (NumDelayCountS0 == NumDelayTicksS2)
                    {
                        DelayS2 = false;
                        NumDelayCountS2 = 0;
                    }
                    //checks if collision time is not complete
                    if (NumDelayCountS2 < NumDelayTicksS2)
                    {
                        NumDelayCountS2++;
                    }
                }
                else
                {
                    if (!CollisionS0 && !CollisionS1 && !CollisionS2)
                    {
                        //checks is there is transmission going on currently
                        if (!S2Transmission)
                        {
                            if (!S2LastMessage)
                            {
                                Station2ticks = 0;
                            }

                            probability3 = (float) rand() / (float) RAND_MAX;
                            Station2Dest = getRandomNumberInclusive(1, 2);
                            Station2MessageLength = getRandomNumberInclusive(1, 3);

                            if (probability3 > PROBABILITY_REQUIRED_TO_SEND_MSG)
                            {
                                S2Transmission = true;
                                Station2--;
                                Station2ticks++;
                            }
                        }
                        else
                        {
                            Station2--;
                            Station2ticks++;
                        }
                    }
                    else
                    {
                        S2LastMessage = true;
                        S2Transmission = false;
                        Station2 = 16;
                        NumDelayTicksS2 = getRandomNumberInclusive(1, 24);
                        DelayS2 = true;
                        NumDelayCountS2 = 1;
                    }
                }
                if (Station2Dest == 1 && Station2 == 8)
                {
                    TotalNoTicksS2 = TotalNoTicksS2 + Station2ticks;
                    Station2SucessfulTransmission++;
                    S2LastMessage = false;
                    Station2ticks = 0;
                    S2Transmission = false;
                    Station2 = 16;
                    Station2Dest = 0;
                }
                if (Station2Dest == 2 && Station2 == 0)
                {
                    TotalNoTicksS2 = TotalNoTicksS2 + Station2ticks;
                    Station2SucessfulTransmission++;
                    S2LastMessage = false;
                    Station2ticks = 0;
                    S2Transmission = false;
                    Station2 = 16;
                    Station2Dest = 0;
                }
            }
        }
    }

    cout << "Total Number of Successful transmission in Station 0:  " << Station0SucessfulTransmission << endl;

    int latency = getLatency(TotalNoTicksS0, Station0SucessfulTransmission);
    latency != -1 ? cout << "Latency Occurred in Station 0 = " << latency << endl : cout << "";

    cout << "Total Number of Successful transmission in Station 1:  " << Station1SucessfulTransmission << endl;

    latency = getLatency(TotalNoTicksS1, Station1SucessfulTransmission);
    latency != -1 ? cout << "Latency Occurred in Station 1 = " << latency << endl : cout << "";


    cout << "Total Number of Successful transmission in Station 2:  " << Station2SucessfulTransmission << endl;

    latency = getLatency(TotalNoTicksS2, Station2SucessfulTransmission);
    latency != -1 ? cout << "Latency Occurred in Station 2 = " << latency << endl : cout << "";

    cout << endl;

    return 0;
}
