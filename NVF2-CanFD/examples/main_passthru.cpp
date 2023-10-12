/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Exploring-CanBus
** File description:
** main_passthru
*/

#include <Arduino.h>

#define BOARD_UNO

#ifdef BOARD_UNO
#define CAN_CSN1             10
#define CAN_CSN2             9
#endif

#define DELAY_MS            250

// include Serial Before NVF_Can to override Serial to SerialUSB
#include "CanFD/NVF_Can.h"

// CAN Network 1
MCP_CAN NVFCanI0(CAN_CSN1);
NVF_Can NVFCan0(&NVFCanI0, 0x01);

// CAN Network 2
MCP_CAN NVFCanI1(CAN_CSN2);
NVF_Can NVFCan1(&NVFCanI1, 0x01);

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