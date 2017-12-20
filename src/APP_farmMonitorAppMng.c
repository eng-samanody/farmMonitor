
#include <Arduino_FreeRTOS.h>
#include "APP_farmMonitorAppMng.h"


extern void APP_vidFarmMonitorTaskCallback(void *pvParameters){
    TickType_t xLastWakeTime;
    const TickType_t xPeriod =  pdMS_TO_TICKS (APP_MNG_TSK_PERIOD);
    xLastWakeTime = xTaskGetTickCount();
    for(;;){
        vTaskDelayUntil( &xLastWakeTime, xPeriod );
        //INFO(" App tsk ");

    }
}