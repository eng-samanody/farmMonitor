#ifndef LOG_SERIAL_DEBUG_H__
#define LOG_SERIAL_DEBUG_H__

#include "TYPE_stdTypes.h"

#define SERIAL_DEBUGGER_BAUD_RATE__ 9600u

#define INFO(...) LOG_vidPrintLn((char*)__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

    //extern void LOG_vidDebugInit(void);
    extern void LOG_vidPrint(char * format, ...);
    extern void LOG_vidPrintLn(char * format, ...);

#ifdef __cplusplus
} // extern "C"
#endif




//#define DEBUG_PRINT(...)       Serial.print(__VA_ARGS__)
//#define DEBUG_PRINTLN(...)     Serial.println(__VA_ARGS__)

#endif /* LOG_SERIAL_DEBUG_H__ */