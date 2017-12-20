#include "BUZ_buzzerMng.h"
#include <Arduino_FreeRTOS.h>
#include <Arduino.h>


typedef enum {
	BUZZER_OFF,
	BUZZER_ON,
}tenuBuzzerState;

typedef enum {
	BUZZER_ON_SLOW,
	BUZZER_ON_MEDIUM,
	BUZZER_ON_FAST,
}tenuBuzzerSpeed;

static uint8_t u8BuzzerState;
static uint8_t u8BuzzerSpeed;
static uint32_t u32BuzzingPeriod;

extern void BUZ_vidBuzzerOn(void){
	if (u8BuzzerState!=BUZZER_ON){
		u8BuzzerState = BUZZER_ON;
		u32BuzzingPeriod = 0u;
		u8BuzzerSpeed = BUZZER_ON_SLOW;
	}
}

extern void BUZ_vidBuzzerOff(void){
	u8BuzzerState = BUZZER_OFF;
	u8BuzzerSpeed = BUZZER_ON_SLOW;
}

extern void BUZ_vidInit(void){
	//TODO:: abstract arduino functions to standard MCAL
	pinMode(BUZZER_PIN, OUTPUT);
	digitalWrite(BUZZER_PIN, HIGH);

	u8BuzzerState = BUZZER_OFF;///////////////////////////////////
	u8BuzzerSpeed = BUZZER_ON_SLOW;
	u32BuzzingPeriod = 0u; 
}

static void toggleBuzzer(void){
	//TODO:: abstract arduino functions to standard MCAL
    digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN)); // toggle buzzer
   // Serial.println((String) "u8BuzzerSpeed = " + u8BuzzerSpeed + " u8BuzzerState = " + u8BuzzerState);
}

static void shutBuzzerOff(void){
	digitalWrite(BUZZER_PIN, HIGH);
 //Serial.println((String) "u8BuzzerSpeed = " + u8BuzzerSpeed + " u8BuzzerState = " + u8BuzzerState);
}

extern void BUZ_buzzerToneTaskCallback(void *pvParameters){ 
   
	for(;;){
		if(u8BuzzerState==BUZZER_ON){
    
			switch(u8BuzzerSpeed){
				case BUZZER_ON_SLOW :
					do{					
						toggleBuzzer();	
						vTaskDelay( SLOW_BUZZ_INTERVAL / portTICK_PERIOD_MS ); // wait for SLOW_BUZZ_INTERVAL
						u32BuzzingPeriod+=SLOW_BUZZ_INTERVAL;							
					} while(u32BuzzingPeriod<=SLOW_BUZZ_PERIOD);
					u32BuzzingPeriod=0;
					u8BuzzerSpeed=BUZZER_ON_MEDIUM;	
				break;
				case BUZZER_ON_MEDIUM :				
					do{
						toggleBuzzer();													
						vTaskDelay( MEDIUM_BUZZ_INTERVAL / portTICK_PERIOD_MS ); // wait for MEDIUM_BUZZ_INTERVAL
						u32BuzzingPeriod+=MEDIUM_BUZZ_INTERVAL;
					} while(u32BuzzingPeriod<=MEDIUM_BUZZ_PERIOD);
					u32BuzzingPeriod=0;
					u8BuzzerSpeed=BUZZER_ON_FAST;
				break;
				case BUZZER_ON_FAST :				
					do{					
						toggleBuzzer();
						vTaskDelay( FAST_BUZZ_INTERVAL / portTICK_PERIOD_MS ); // wait for FAST_BUZZ_INTERVAL
						u32BuzzingPeriod+=FAST_BUZZ_INTERVAL;
					} while (u32BuzzingPeriod<=FAST_BUZZ_PERIOD);
					u8BuzzerState = BUZZER_OFF;
					u32BuzzingPeriod = 0;
					u8BuzzerSpeed=BUZZER_ON_SLOW;
				break;
				default:
				break ;
			}
		} else {
			shutBuzzerOff();
			vTaskDelay( BUZZER_TSK_PERIOD / portTICK_PERIOD_MS ); // wait for BUZZER_TSK_PERIOD
   	}
	}
}
