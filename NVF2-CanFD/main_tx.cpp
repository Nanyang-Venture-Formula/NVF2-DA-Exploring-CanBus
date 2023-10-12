/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Exploring-CanBus
** File description:
** main_tx
*/



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

MCP_CAN NVFCanI0(CAN_CSN);
NVF_Can NVFCan0(&NVFCanI0, 0x0F);

void setup()
{
  Serial.begin(115200);
  NVFCan0.setup();
}

uint8_t data[8] = { 0xFF, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xF0, 0xFF};

can_frame tx_buf;
void loop()
{
  memcpy(tx_buf.data, data, 8);
  tx_buf.can_dlc = 8;

  NVFCan0.tx(&tx_buf);
  delay(DELAY_MS);   // send data per 100ms
}