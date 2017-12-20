#include "LOG_serialDebugger.h"
#include <stdarg.h>
#include <stdio.h>
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

    BOOL bolSerialInitialized = FALSE;

    static void vidDebugInit(void){
        Serial.begin(SERIAL_DEBUGGER_BAUD_RATE__);
    }

    extern void LOG_vidPrint(char * format, ...){
        if ( ! bolSerialInitialized ){
            vidDebugInit();
            bolSerialInitialized = TRUE;
        }
        char debugMsg[100];
        va_list ap;
        va_start(ap, format);
        vsnprintf(debugMsg, 100, format, ap);
        Serial.print(debugMsg);
        va_end(ap);

    }

    extern void LOG_vidPrintLn(char * format, ...){
        if ( ! bolSerialInitialized ){
            vidDebugInit();
            bolSerialInitialized = TRUE;
        }
        char debugMsg[100];
        va_list ap;
        va_start(ap, format);
        vsnprintf(debugMsg, 100, format, ap);
        Serial.println(debugMsg);
        va_end(ap);  
    }
#ifdef __cplusplus
} // extern "C"
#endif

