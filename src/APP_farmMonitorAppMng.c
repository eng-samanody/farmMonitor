
#include <Arduino_FreeRTOS.h>
#include "APP_farmMonitorAppMng.h"
#include "BUZ_buzzerMng.h"



static uint8 u8CheckTempLevel(void){    
    uint16 u16TempratureValDEC = tempratureValC * 10;
    uint8 u8LevelState = LEVEL_OK;
    if(u16TempratureValDEC > TEMP_MAX_LEVEL || u16TempratureValDEC < TEMP_MIN_LEVEL){
        u8TempLevelState = LEVEL_NOK;
    }
    return u8LevelState;
}

static uint8 u8CheckHumLevel(void){    
    uint16 u16HumValDEC = humidityValue * 10;
    uint8 u8LevelState = LEVEL_OK;
    if(u16HumValDEC > HUMD_MAX_LEVEL){
        u8HumLevelState = LEVEL_NOK;
    } 
    return u8LevelState;
}

static uint8 u8CheckDustLevel(void){  
    uint16 u16DustValDEC = fDustDensity * 10;
    uint8 u8LevelState = LEVEL_OK;
    if(u16DustValDEC > DUST_MAX_LEVEL){
        u8LevelState = LEVEL_NOK;
    } 
    return u8LevelState;
}

static uint8 u8CheckLightLevel(void){    
    uint16 u16LuxValDEC = u32Lux * 10;
    uint8 u8LevelState = LEVEL_OK;
    if(u16LuxValDEC < LIGHT_MIN_LEVEL){
        u8LightLevelState = LEVEL_NOK;
    }
    return u8LevelState;
}

static void vidAppInit(void){
    u8TempLevelState = LEVEL_OK;
    u8HumLevelState = LEVEL_OK;
    u8LightLevelState = LEVEL_OK;
    u8DustLevelState = LEVEL_OK;
}



    // extern float humidityValue;
    // extern float tempratureValC;
    // extern uint16 u16Luminicity;
    // extern uint32 u32Lux;
    //uint16 u16HumidityValue  = humidityValue  * 10;

extern void APP_vidFarmMonitorTaskCallback(void *pvParameters){
    TickType_t xLastWakeTime;
    const TickType_t xPeriod =  pdMS_TO_TICKS (APP_MNG_TSK_PERIOD);
    xLastWakeTime = xTaskGetTickCount();
    static uint32 u32TempNokLevelTimeCount = 0;
    static uint32 u32TempNokLevelTimeCountReBuzz = 0;
    static BOOL boolTempNokLevelSmsSentFlag = FALSE;
    static uint32 u32HumdNokLevelTimeCount = 0;
    static uint32 u32HumdNokLevelTimeCountReBuzz = 0;
    static uint32 u32DustNokLevelTimeCount = 0;
    static uint32 u32LightNokLevelTimeCount = 0;
    for(;;){
        vTaskDelayUntil( &xLastWakeTime, xPeriod );
        //INFO(" App tsk ");

        uint8 u8NewDustLevelState = u8CheckDustLevel();
        uint8 u8NewLightLevelState = u8CheckLightLevel();
        //u8TempLevelState ||  u8HumLevelState || u8LightLevelState || u8DustLevelState == LEVEL_NOK

        /*===============================================================================================*/
        /*====================================== TMP MONITOR ============================================*/
        /*===============================================================================================*/        
        uint8 u8NewTempLevelState = u8CheckTempLevel();
        if (u8TempLevelState == LEVEL_NOK && u8NewTempLevelState == LEVEL_NOK){
            u32TempNokLevelTimeCount += APP_MNG_TSK_PERIOD;
            u32TempNokLevelTimeCountReBuzz += APP_MNG_TSK_PERIOD;
            if( u32TempNokLevelTimeCount >= SMS_ALERT_TIME && boolTempNokLevelSmsSentFlag == FALSE){
                //TODO::SEND SMS
                //TODO::LOG TO EEP
            }
            if(u32TempNokLevelTimeCount >= BUZ_REALERT_TIME){
                u32TempNokLevelTimeCountReBuzz = 0;
                BUZ_vidBuzzerOn();
            }
        }

        if (u8TempLevelState == LEVEL_NOK && u8NewTempLevelState == LEVEL_OK){
            u8TempLevelState = LEVEL_OK;
            //TODO:TEMP LED GREEN
            //TODO::LOG TO EEP
            if( u32TempNokLevelTimeCount >= SMS_ALERT_TIME){
                //TODO::SEND SMS
            }
            u32TempNokLevelTimeCount = 0;
            u32TempNokLevelTimeCountReBuzz = 0;
        }

        if (u8TempLevelState == LEVEL_OK && u8NewTempLevelState == LEVEL_NOK){
            u8TempLevelState = LEVEL_NOK;
            BUZ_vidBuzzerOn();
            //TODO:TEMP LED RED
            //TODO::LOG TO EEP
        }



        /*===============================================================================================*/
        /*====================================== HUM MONITOR ============================================*/
        /*===============================================================================================*/
        uint8 u8NewHumLevelState = u8CheckHumLevel();
        if (u8HumLevelState == LEVEL_OK){
            u8NewHumLevelState  = u8CheckHumLevel();
            if (u8NewHumLevelState == LEVEL_NOK){
                u8HumLevelState = LEVEL_NOK;
                BUZ_vidBuzzerOn();
            }
        } else {
            u32HumdNokLevelTimeCount++;
            //TODO::LOG TO EEP
            if( u32HumdNokLevelTimeCount >= SMS_ALERT_TIME){
                //TODO::SEND SMS
            }
        }

        if (u8LightLevelState == LEVEL_NOK){
            BUZ_vidBuzzerOn();
        }

        if (u8DustLevelState == LEVEL_NOK){
            BUZ_vidBuzzerOn();
        }


    }
}