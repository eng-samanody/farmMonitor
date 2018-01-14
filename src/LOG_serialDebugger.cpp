#include "LOG_serialDebugger.h"
#include <stdarg.h>
#include <stdio.h>
#include <Arduino.h>
#include "NeoHWSerial.h"

#ifdef __cplusplus
extern "C" {
#endif

    BOOL bolSerialInitialized = FALSE;

    static void vidDebugInit(void){
        NeoSerial.begin(SERIAL_DEBUGGER_BAUD_RATE__);
        bolSerialInitialized = TRUE;
    }

    extern void LOG_vidPrint(char * format, ...){
        if ( ! bolSerialInitialized ){
            vidDebugInit();
            bolSerialInitialized = TRUE;
        }
        char debugMsg[DBG_BUF_MAX_SIZE];
        va_list ap;
        va_start(ap, format);
        vsnprintf(debugMsg, DBG_BUF_MAX_SIZE, format, ap);
        NeoSerial.print(debugMsg);
        va_end(ap);

    }

    extern void LOG_vidPrintLn(char * format, ...){
        if ( ! bolSerialInitialized ){
            vidDebugInit();
            bolSerialInitialized = TRUE;
        }
        char debugMsg[DBG_BUF_MAX_SIZE];
        va_list ap;
        va_start(ap, format);
        vsnprintf(debugMsg, DBG_BUF_MAX_SIZE, format, ap);
        NeoSerial.println(debugMsg);
        va_end(ap);  
    }
#ifdef __cplusplus
} // extern "C"
#endif

