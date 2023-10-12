#include <Arduino.h>

// #define BOARD_PICO
// #define BOARD_BLUEPILL
// #define BOARD_M5STACK
#define BOARD_UNO

#ifdef BOARD_UNO
#define CAN_CSN             10
#endif
#ifdef BOARD_PICO
#define CAN_CSN             10
#define CAN_INT             11
#define Serial              SerialUSB
#endif
#ifdef BOARD_BLUEPILL
#define CAN_CSN             PB0
#define CAN_INT             PA4
#define Serial              Serial1
#endif
#ifdef BOARD_M5STACK
#define CAN_CSN             21
#define CAN_INT             22
// #define Serial              SerialUSB
#endif

#define DELAY_MS            250

// include Serial Before NVF_Can to override Serial to SerialUSB
#include "CanFD/NVF_Can.h"

NVF_Can NVFCan0(CAN_CSN, 0x0F);
NVF_Can NVFCan1(CAN_CSN+1, 0x0F);

void setup()
{
  Serial.begin(115200);
  NVFCan0.setup();
  NVFCan1.setup();
}

can_frame rx_buf0;
can_frame rx_buf1;

void loop()
{
  if (NVFCan0.taskLoopRecv(&rx_buf0))
  {
    NVFCan1.tx(&rx_buf0);
  }

  if (NVFCan1.taskLoopRecv(&rx_buf1))
  {
    NVFCan0.tx(&rx_buf1);
  }
}