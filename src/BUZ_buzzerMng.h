#ifndef BUZZER_MNG_H_
#define BUZZER_MNG_H_

#include "BUZ_buzzerConf.h"

#ifdef __cplusplus
extern "C" {
#endif


#define BUZZER_INIT_STATE 		0u
#define SLOW_BUZZ_INTERVAL 		500u
#define MEDIUM_BUZZ_INTERVAL 	250u
#define FAST_BUZZ_INTERVAL 		50u

#define BUZZER_TSK_PERIOD (uint16_t)500
#define BUZ_TSK_STACK_SIZE (uint8_t)128


extern void BUZ_buzzerToneTaskCallback(void *pvParameters);
extern void BUZ_vidBuzzerOn(void);
extern void BUZ_vidBuzzerOff(void);
extern void BUZ_vidInit(void);


#ifdef __cplusplus
} // extern "C"
#endif

#endif //BUZZER_MNG_H


