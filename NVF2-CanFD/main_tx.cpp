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

uint8_t counter_buf = 0;

can_frame tx_buf;
void loop()
{
  if (counter_buf == -2) counter_buf = 0;

  tx_buf.data[0] = 0x00 + counter_buf;
  tx_buf.data[1] = 0xFF - counter_buf;

  tx_buf.can_dlc = 2;
  NVFCan0.tx(data, tx_buf.can_dlc);
  delay(DELAY_MS);   // send data per 100ms
}