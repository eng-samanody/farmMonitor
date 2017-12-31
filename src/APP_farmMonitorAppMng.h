#ifndef  APP_MNG_H__
#define APP_MNG_H__

#include "APP_farmMonitorAppConf.h"
#include "TYPE_stdTypes.h"

typedef enum{
    LEVEL_NOK,
    LEVEL_OK,
} enutLevelState;

uint8 u8TempLevelState;
uint8 u8HumLevelState;
uint8 u8LightLevelState;
uint8 u8DustLevelState;


extern float humidityValue;
extern float tempratureValC;

extern uint16 u16Luminicity;
extern uint32 u32Lux;

extern float fDustDensity;






#endif 