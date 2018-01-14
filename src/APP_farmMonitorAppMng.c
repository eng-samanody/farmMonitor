
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

extern void APP_vidFarmMonitorTaskCallback(void *pvParameters){
    TickType_t xLastWakeTime;
    const TickType_t xPeriod =  pdMS_TO_TICKS (APP_MNG_TSK_PERIOD);
    xLastWakeTime = xTaskGetTickCount();

    for(;;){
        vTaskDelayUntil( &xLastWakeTime, xPeriod );
        //INFO(" App tsk ");

        /*===============================================================================================*/
        /*====================================== TMP MONITOR ============================================*/
        /*===============================================================================================*/ 
        static uint32 u32TempNokLevelTimeCount = 0;
        static uint32 u32TempNokLevelTimeCountReBuzz = 0;
        static BOOL boolTempNokLevelSmsSentFlag = FALSE;       
        uint8 u8NewTempLevelState = u8CheckTempLevel();
        if (u8TempLevelState == LEVEL_NOK && u8NewTempLevelState == LEVEL_NOK){
            u32TempNokLevelTimeCount += APP_MNG_TSK_PERIOD;
            u32TempNokLevelTimeCountReBuzz += APP_MNG_TSK_PERIOD;
            if( u32TempNokLevelTimeCount >= SMS_ALERT_TIME && boolTempNokLevelSmsSentFlag == FALSE){
                boolTempNokLevelSmsSentFlag = TRUE;
                //TODO::SEND SMS
                //TODO::LOG TO EEP1234
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
            boolTempNokLevelSmsSentFlag = FALSE;
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
        static uint32 u32HumdNokLevelTimeCount = 0;
        static uint32 u32HumdNokLevelTimeCountReBuzz = 0;
        static BOOL boolHumNokLevelSmsSentFlag = FALSE;
        uint8 u8NewHumLevelState = u8CheckHumLevel();
        if (u8HumLevelState == LEVEL_NOK && u8NewHumLevelState == LEVEL_NOK){
            u32HumdNokLevelTimeCount += APP_MNG_TSK_PERIOD;
            u32HumdNokLevelTimeCountReBuzz += APP_MNG_TSK_PERIOD;
            //if time elapsed and message not yet sent
            if( u32HumdNokLevelTimeCount >= SMS_ALERT_TIME && boolHumNokLevelSmsSentFlag == FALSE){
                boolHumNokLevelSmsSentFlag = TRUE;
                //TODO::SEND SMS
                //TODO::LOG TO EEP
            }
            if(u32HumdNokLevelTimeCount >= BUZ_REALERT_TIME){
                u32HumdNokLevelTimeCountReBuzz = 0;
                BUZ_vidBuzzerOn();
            }
        }
        if (u8HumLevelState == LEVEL_NOK && u8NewHumLevelState == LEVEL_OK){
            u8HumLevelState = LEVEL_OK;
            //TODO:HUM LED GREEN
            //TODO::LOG TO EEP
            if( u32HumdNokLevelTimeCount >= SMS_ALERT_TIME){
                //TODO::SEND SMS
            }
            u32HumdNokLevelTimeCount = 0;
            u32HumdNokLevelTimeCountReBuzz = 0;
            boolHumNokLevelSmsSentFlag = FALSE;
        }
        if (u8HumLevelState == LEVEL_OK && u8NewHumLevelState == LEVEL_NOK){
            u8HumLevelState = LEVEL_NOK;
            BUZ_vidBuzzerOn();
            //TODO:HUM LED RED
            //TODO::LOG TO EEP
        }
        
        /*===============================================================================================*/
        /*====================================== DUST MONITOR ===========================================*/
        /*===============================================================================================*/
        static uint32 u32DustNokLevelTimeCount = 0;
        static uint32 u32DustNokLevelTimeCountReBuzz = 0;
        static BOOL boolDustNokLevelSmsSentFlag = FALSE;
        uint8 u8NewDustLevelState = u8CheckDustLevel();
        if (u8DustLevelState == LEVEL_NOK && u8NewDustLevelState == LEVEL_NOK){
            u32DustNokLevelTimeCount += APP_MNG_TSK_PERIOD;
            u32DustNokLevelTimeCountReBuzz += APP_MNG_TSK_PERIOD;
            //if time elapsed and message not yet sent
            if( u32DustNokLevelTimeCount >= SMS_ALERT_TIME && boolDustNokLevelSmsSentFlag == FALSE){
                boolDustNokLevelSmsSentFlag = TRUE;
                //TODO::SEND SMS
                //TODO::LOG TO EEP
            }
            if(u32DustNokLevelTimeCount >= BUZ_REALERT_TIME){
                u32DustNokLevelTimeCountReBuzz = 0;
                BUZ_vidBuzzerOn();
            }
        }
        if (u8DustLevelState == LEVEL_NOK && u8NewDustLevelState == LEVEL_OK){
            u8DustLevelState = LEVEL_OK;
            //TODO:Dust LED GREEN
            //TODO::LOG TO EEP
            if( u32DustNokLevelTimeCount >= SMS_ALERT_TIME){
                //TODO::SEND SMS
            }
            u32DustNokLevelTimeCount = 0;
            u32DustNokLevelTimeCountReBuzz = 0;
            boolDustNokLevelSmsSentFlag = FALSE;
        }
        if (u8DustLevelState == LEVEL_OK && u8NewDustLevelState == LEVEL_NOK){
            u8DustLevelState = LEVEL_NOK;
            BUZ_vidBuzzerOn();
            //TODO:Dust LED RED
            //TODO::LOG TO EEP
        }

        /*===============================================================================================*/
        /*====================================== LIGHT MONITOR ==========================================*/
        /*===============================================================================================*/
        static uint32 u32LightNokLevelTimeCount = 0;
        static uint32 u32LighttNokLevelTimeCountReBuzz = 0;
        static BOOL boolLighttNokLevelSmsSentFlag = FALSE;
        uint8 u8NewLightLevelState = u8CheckLightLevel();
        if (u8LightLevelState == LEVEL_NOK && u8NewLightLevelState == LEVEL_NOK){
            u32LightNokLevelTimeCount += APP_MNG_TSK_PERIOD;
            u32LighttNokLevelTimeCountReBuzz += APP_MNG_TSK_PERIOD;
            //if time elapsed and message not yet sent
            if( u32LightNokLevelTimeCount >= SMS_ALERT_TIME && boolLighttNokLevelSmsSentFlag == FALSE){
                boolLighttNokLevelSmsSentFlag = TRUE;
                //TODO::SEND SMS
                //TODO::LOG TO EEP
            }
            if(u32LightNokLevelTimeCount >= BUZ_REALERT_TIME){
                u32LighttNokLevelTimeCountReBuzz = 0;
                BUZ_vidBuzzerOn();
            }
        }
        if (u8LightLevelState == LEVEL_NOK && u8NewLightLevelState == LEVEL_OK){
            u8LightLevelState = LEVEL_OK;
            //TODO:: Light LED GREEN
            //TODO:: LOG TO EEP
            if( u32LightNokLevelTimeCount >= SMS_ALERT_TIME){
                //TODO::SEND SMS
            }
            u32LightNokLevelTimeCount = 0;
            u32LighttNokLevelTimeCountReBuzz = 0;
            boolLighttNokLevelSmsSentFlag = FALSE;
        }
        if (u8LightLevelState == LEVEL_OK && u8NewLightLevelState == LEVEL_NOK){
            u8LightLevelState = LEVEL_NOK;
            BUZ_vidBuzzerOn();
            //TODO:: Light LED RED
            //TODO:: LOG TO EEP
        }
    }
}