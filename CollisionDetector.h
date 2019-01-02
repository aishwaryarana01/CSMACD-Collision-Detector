#ifndef ADVOS_COLLISIONDETECTOR_H
#define ADVOS_COLLISIONDETECTOR_H

bool isFirstStationCollided(int Station0, int Station2, int StationS0, int StationS2);
bool isSecondStationCollided(int Station0, int Station2, int StationS0, int StationS2, int Station0MessageLength, int Station2MessageLength, int CarrierLength);
bool isThirdStationCollided(int Station0, int Station2, int StationS0, int StationS2);

#endif //ADVOS_COLLISIONDETECTOR_H