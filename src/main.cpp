#include <Arduino.h>
#include "Arduino_FreeRTOS.h"
#include "BUZ_buzzerMng.h"
#include "DUS_dustSensorMng.h"
#include "DHT_tempHumiditySensorMng.h"
#include "LOG_serialDebugger.h"

#include "LIT_lightSensorMng.h"

#include <String.h>

#include "TYPE_stdTypes.h"

extern float humidityValue;
extern float tempratureValC;

extern uint16 u16Luminicity;
extern uint32 u32Lux;

 
void TST_vidTestTaskCallback(void *pvParameters);
void TST_vidTestTaskCallback(void *pvParameters){
  TickType_t xLastWakeTime;
  //pdMS_TO_TICKS(X) ( ((unsigned short) X * (unsigned short) ((unsigned long)128000 >> 11)) / (unsigned short)1000 ) 
  const TickType_t xPeriod =  pdMS_TO_TICKS (2000);
  xLastWakeTime = xTaskGetTickCount();
  for(;;){
    vTaskDelayUntil( &xLastWakeTime, xPeriod );
    //BUZ_vidBuzzerOn();
    //Serial.println((String)"humidityValue = "+humidityValue+"% , tempratureValC = "+tempratureValC+" *C");
    Serial.println((float)(humidityValue),3);
    Serial.println((float)(tempratureValC),3);
    Serial.println(u16Luminicity);
    Serial.println(u32Lux);
    Serial.print("millis : "); Serial.println(millis());
    //LOG_vidPrintLn((char*)"tempratureValC %lf", tempratureValC );
   //(TickType_t)( (uint32_t)128000 >> (portUSE_WDTO + 11) )
   //( ( TickType_t ) ( 2000 ) * ( TickType_t ) configTICK_RATE_HZ ) / ( TickType_t ) 1000 ) 
   //( ((unsigned short) 2000 * (unsigned short) ((unsigned long)128000 >> 11)) / (unsigned short)1000 ) 
    //Serial.println("hello");
  }
}


void setup() {
  // put your setup code here, to run once:
  //BUZ_vidInit();
  Serial.begin(9600);
  /* Low priority numbers denote low priority tasks */
  //xTaskCreate(BUZ_buzzerToneTaskCallback, (const portCHAR *)"BUZZER_TASK", 128, NULL, 7, NULL ); /* Period 500 ms*/
  xTaskCreate(DUST_readDustSensorTaskCallback, (const portCHAR *)"DUST_TASK", 128, NULL, 6, NULL ); /* Period 1000 ms*/
  xTaskCreate(DHT_vidUpdateDhtTaskCallback, (const portCHAR *)"DHT_TASK", 128*4, NULL, 5, NULL ); /* Period 3000 ms*/
  xTaskCreate(LIT_vidUpdateLightTskCbk, (const portCHAR *)"LIGHT_TASK", 128*2, NULL, 5, NULL ); /* Period 1200 ms*/
  xTaskCreate(TST_vidTestTaskCallback,  (const portCHAR *)"TEST_TASK",  128, NULL, 4, NULL ); /* Period 10000 ms*/
}

void loop() {
  // put your main code here, to run repeatedly:

  //humidityValue = DHT_readHumidity(FALSE);
  // Read temperature as Celsius (the default)
  //tempratureValC = DHT_readTemperature('C',FALSE);

  //LOG_vidPrintLn("log %d", i);
  //Serial.print((String)"H : "+ humidityValue11 + " % , T : "+ tempratureValC22 +" *C\r\n");
  //Serial.println((String)"hello "+ humidityValue11 +"*C\r\n");
  //Serial.println((float)(2.789),3);
  //LOG_vidPrintLn("humidityValue11  %d", humidityValue11 );
  // LOG_vidPrintLn("tempratureValC22 %lf", tempratureValC22 );
  // LOG_vidPrintLn("tempratureValC33 %d", tempratureValC33 );
  //delay(3000);


}