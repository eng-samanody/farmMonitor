
#include <Arduino.h>
#include "Arduino_FreeRTOS.h"
#include "BUZ_buzzerMng.h"
#include "DUS_dustSensorMng.h"
#include "DHT_tempHumiditySensorMng.h"
#include "LOG_serialDebugger.h"
#include "LIT_lightSensorMng.h"
#include <String.h>
#include "TYPE_stdTypes.h"
#include "NeoHWSerial.h"
#include "APP_farmMonitorAppMng.h"


extern float humidityValue;
extern float tempratureValC;
extern uint16 u16Luminicity;
extern uint32 u32Lux;

static volatile uint16_t count = 0;
static void char_received( uint8_t c )
{
  // This is a little naughty, as it will try to block
  //   in this ISR if the tx_buffer is full.  For this example,
  //   we are only sending as many characters as we have received,
  //   and they arrive at the same rate we are sending them.
  NeoSerial.write( c );
  count++;
}
 
void TST_vidTestTaskCallback(void *pvParameters);


// ISR(USART_RX_vect, ISR_BLOCK) {

// }

void setup() {
  NeoSerial.begin( 9600 );
  NeoSerial.attachInterrupt( char_received );
  NeoSerial.println( F("NeoSerial initialized.") );

  // put your setup code here, to run once:
  //BUZ_vidInit();
  //Serial.begin(9600);
  /* Low priority numbers denote low priority tasks */
  xTaskCreate(BUZ_buzzerToneTaskCallback, (const portCHAR *)"BUZZER_TASK", 128, NULL, 7, NULL ); /* Period 500 ms*/
  xTaskCreate(DUST_readDustSensorTaskCallback, (const portCHAR *)"DUST_TASK", 128, NULL, 6, NULL ); /* Period 1000 ms*/
  xTaskCreate(DHT_vidUpdateDhtTaskCallback, (const portCHAR *)"DHT_TASK", 128*4, NULL, 5, NULL ); /* Period 3000 ms*/
  xTaskCreate(LIT_vidUpdateLightTskCbk, (const portCHAR *)"LIGHT_TASK", 128*2, NULL, 5, NULL ); /* Period 1200 ms*/
  //xTaskCreate(TST_vidTestTaskCallback,  (const portCHAR *)"TEST_TASK",  128, NULL, 4, NULL ); /* Period 10000 ms*/
  xTaskCreate(APP_vidFarmMonitorTaskCallback, (const portCHAR *)"APP_TASK", 128*2, NULL, 4, NULL ); /* Period 1200 ms*/
}

void loop() {

  {
    delay( 1000 );

    uint8_t oldSREG = SREG;
    noInterrupts();
    uint16_t old_count = count;
    count = 0;
    SREG = oldSREG;

    if (old_count) {
      NeoSerial.print( '\n' );
      NeoSerial.print( old_count );
      NeoSerial.println( F(" characters echoed") );
    } else {
      NeoSerial.print( '.' );
    }
    NeoSerial.flush();
  }

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


void TST_vidTestTaskCallback(void *pvParameters){
  TickType_t xLastWakeTime;
  //pdMS_TO_TICKS(X) ( ((unsigned short) X * (unsigned short) ((unsigned long)128000 >> 11)) / (unsigned short)1000 ) 
  const TickType_t xPeriod =  pdMS_TO_TICKS (2000);
  xLastWakeTime = xTaskGetTickCount();
  for(;;){
    vTaskDelayUntil( &xLastWakeTime, xPeriod );
    //BUZ_vidBuzzerOn();
    //Serial.println((String)"humidityValue = "+humidityValue+"% , tempratureValC = "+tempratureValC+" *C");
    NeoSerial.println((float)(humidityValue),3);
    NeoSerial.println((float)(tempratureValC),3);
    NeoSerial.println(u16Luminicity);
    NeoSerial.println(u32Lux);
    NeoSerial.print("millis : "); NeoSerial.println(millis());
    //LOG_vidPrintLn((char*)"tempratureValC %lf", tempratureValC );
   //(TickType_t)( (uint32_t)128000 >> (portUSE_WDTO + 11) )
   //( ( TickType_t ) ( 2000 ) * ( TickType_t ) configTICK_RATE_HZ ) / ( TickType_t ) 1000 ) 
   //( ((unsigned short) 2000 * (unsigned short) ((unsigned long)128000 >> 11)) / (unsigned short)1000 ) 
    //Serial.println("hello");
  }
}