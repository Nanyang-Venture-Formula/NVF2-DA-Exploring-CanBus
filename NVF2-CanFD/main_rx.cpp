#include <Arduino.h>

#define BOARD_PICO
// #define BOARD_BLUEPILL
// #define BOARD_M5STACK

#ifdef BOARD_PICO
#define CAN_CSN             5
#define CAN_INT             6
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

// include Serial Before NVF_Can to override Serial to SerialUSB
#include "CanFD/NVF_Can.h"

long unsigned int timerH = 10; 

NVF_Can NVFCan0(CAN_CSN);

void setup()
{
  Serial.begin(115200);
  
  NVFCan0.canId = 0x2345;
  NVFCan0.taskSetup();
//   NVFCan0.attachRecvInterrupt(CAN_INT);
}

void loop()
{
  NVFCan0.taskLoopRecv();
  if (time(0) % 10 == 5)
  {
    Serial.println("nth");
  }
}