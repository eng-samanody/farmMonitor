
#include "LIT_lightSensorMng.h"



#include <Wire.h>
#include "TSL2561.h"

#include "LOG_serialDebugger.h"

#include <Arduino_FreeRTOS.h>

#define LIGHT_SENSOR_TASK_PERIOD 1200

#ifdef __cplusplus
extern "C" {
#endif
  uint16_t u16Luminicity;
  uint32_t u32Lux;
  
  TSL2561 tsl(TSL2561_ADDR_FLOAT); 

  static void vidUpdateLux(void){  
    u16Luminicity = tsl.getLuminosity(TSL2561_VISIBLE); 
    uint32_t lum = tsl.getFullLuminosity();
    uint16_t ir, full;
    ir = lum >> 16;
    full = lum & 0xFFFF;
    u32Lux = tsl.calculateLux(full, ir);
  }


  static void vidInit(void){
    u16Luminicity=0;
    u32Lux=0;
    if (tsl.begin()) {
      INFO("Found sensor");
    } else {
      INFO("No sensor?");
    }
    tsl.setGain(TSL2561_GAIN_16X);      // set 16x gain (for dim situations)
    tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);  // shortest integration time (bright light)
  }


  extern void LIT_vidUpdateLightTskCbk(void *pvParameters){
    TickType_t xLastWakeTime;
    const TickType_t xPeriod =  pdMS_TO_TICKS (LIGHT_SENSOR_TASK_PERIOD);
    xLastWakeTime = xTaskGetTickCount();

    vidInit();

    for(;;){
      
      vTaskDelayUntil( &xLastWakeTime, xPeriod );

      vidUpdateLux();
    }
  }


#ifdef __cplusplus
} // extern "C"
#endif