
#include "DHT_tempHumiditySensorMng.h"
#include <Arduino_FreeRTOS.h>
#include "DHT.h"
#include "LOG_serialDebugger.h"


#ifdef __cplusplus
extern "C" {
#endif
  
  #define DHTTYPE DHT22

  float humidityValue;
  float tempratureValC;

  DHT dht(DHT_PIN, DHTTYPE);

  extern void DHT_vidUpdateDhtTaskCallback(void *pvParameters){

    TickType_t xLastWakeTime;
    const TickType_t xPeriod =  pdMS_TO_TICKS (DHT_TSK_PERIOD);
    xLastWakeTime = xTaskGetTickCount();
    for(;;){
      vTaskDelayUntil( &xLastWakeTime, xPeriod );
      //INFO(" dht tsk ");
      humidityValue = dht.readHumidity();
      // Read temperature as Celsius (the default)
      tempratureValC = dht.readTemperature();
    }
  }


#ifdef __cplusplus
} // extern "C"
#endif