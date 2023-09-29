#include <Arduino.h>

// #define BOARD_PICO
#define BOARD_BLUEPILL
// #define BOARD_M5STACK

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

#define DELAY_MS            1500

// include Serial Before NVF_Can to override Serial to SerialUSB
#include "CanFD/NVF_Can.h"

NVF_Can NVFCan0(CAN_CSN);

void setup()
{
  Serial.begin(115200);
  NVFCan0.canId = 0x1234;
  NVFCan0.taskSetup();
}

byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

void loop()
{
  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  for (int i = 0; i < 8; i++)
  {
    data[i] = random(0,255);
  }
  NVFCan0.taskLoopSend(data, 8);
  delay(DELAY_MS);   // send data per 100ms
}