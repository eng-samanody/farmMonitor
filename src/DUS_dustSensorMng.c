#include "DUS_dustSensorMng.h"
#include <Arduino_FreeRTOS.h>
#include <Arduino.h>

#define LED_ON  (uint8_t)0
#define LED_OFF (uint8_t)1


extern void DUST_vidInit(void){
  fvoltMeasured = 0;
  fCalcVoltage = 0;
  fDustDensity = 0;
  pinMode(DUST_LED_POWER_PIN,OUTPUT);
}


extern void DUST_readDustSensorTaskCallback(void *pvParameters){
  TickType_t xLastWakeTime;
  const TickType_t xPeriod =  pdMS_TO_TICKS (DUST_TSK_PERIOD);
  /* The xLastWakeTime variable needs to be initialized with the current tick count.  
  * Note that this is the only time the variable is written to explicitly.
  * After this assignment, xLastWakeTime is updated automatically internally within vTaskDelayUntil(). */
  xLastWakeTime = xTaskGetTickCount();


  for(;;){
    /* This task should execute every DUST_TSK_PERIOD milliseconds.  Time is measured in ticks.  
    The pdMS_TO_TICKS macro is used to convert milliseconds into ticks.  
    xLastWakeTime is automatically updated within vTaskDelayUntil() 
    so is not explicitly updated by the task. */
    vTaskDelayUntil( &xLastWakeTime, xPeriod );
    //Serial.println(millis());
    digitalWrite(DUST_LED_POWER_PIN,LED_ON); // power on the LED
    delayMicroseconds(280);
    fvoltMeasured = analogRead(DUST_MEASURE_PIN); // read the dust value
    delayMicroseconds(40);
    digitalWrite(DUST_LED_POWER_PIN,LED_OFF); // turn the LED off
    fCalcVoltage = fvoltMeasured * (5.0 / 1023.0);
    fDustDensity = 0.17 * fCalcVoltage - 0.1;
    //Serial.println((String)"-Raw Signal Value (0-1023): " + voMeasured);
    //Serial.print(" - Voltage: "); Serial.print(calcVoltage);
    //Serial.println((String)"-Dust : " + dustDensity); // unit: mg/m3
    //Serial.println(millis());
  }
}