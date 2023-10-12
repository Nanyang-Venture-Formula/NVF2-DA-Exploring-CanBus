#include <Arduino.h>

// #define BOARD_PICO
// #define BOARD_BLUEPILL
// #define BOARD_M5STACK
#define BOARD_UNO

#ifdef BOARD_UNO
#define CAN_CSN             10
#endif
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

// long unsigned int timerH = 10; 
MCP_CAN NVFCanI0(CAN_CSN);
NVF_Can NVFCan0(&NVFCanI0, 0x01);

void setup()
{
  Serial.begin(115200);
  NVFCan0.setup();
}

can_frame rx_buf;

void loop()
{
  if (NVFCan0.taskLoopRecv(&rx_buf))
  {
      Serial.print(rx_buf.can_id, HEX);
      Serial.print(": ");
      Serial.print(rx_buf.can_dlc);
      Serial.print("->");

    for (int i = 0; i < rx_buf.can_dlc; i++)
    {
      Serial.print(rx_buf.data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}