#ifndef DUST_SENSOR_MNG_H_
#define DUST_SENSOR_MNG_H_

#include "DUS_dustSensorConf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DUST_TSK_PERIOD (uint16_t)1000

float fvoltMeasured;
float fCalcVoltage;
float fDustDensity;

extern void DUST_vidInit(void);
extern void DUST_readDustSensorTaskCallback(void *pvParameters);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* DUST_SENSOR_MNG_H_ */