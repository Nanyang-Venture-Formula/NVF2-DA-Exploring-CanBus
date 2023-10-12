/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** NVF_Can
*/

#ifndef NVF_CAN_H_
#define NVF_CAN_H_

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include <stdint.h>

#define ul unsigned long

struct can_frame
{
  unsigned long can_id = 0xFF;
  uint8_t can_dlc;
  uint8_t data[8];
};

class NVF_Can
{
private:
  ul thisCanID;
  MCP_CAN *CAN;

public:
  NVF_Can(MCP_CAN *CAN, unsigned long canId);
  bool setup();
  bool tx(can_frame *);
  //   void taskSetup(void);
  bool taskLoopRecv(can_frame *);
  //   bool taskLoopSend(byte *, uint);
};

NVF_Can::NVF_Can(MCP_CAN *CAN, unsigned long canId)
{
  this->thisCanID = canId;
  this->CAN = CAN;
}

bool NVF_Can::setup()
{
  SPI.begin();
  while (CAN_OK != this->CAN->begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ))
  {
    Serial.println("CAN BUS initialisation failed");
    delay(500);
  }

  this->CAN->setMode(MCP_NORMAL);
  Serial.println("CAN BUS initialisation successful");
  return 1;
}

bool NVF_Can::tx(can_frame *frame)
{
  this->CAN->sendMsgBuf(frame->can_id, frame->can_dlc, frame->data);
  return 1;
}

bool NVF_Can::taskLoopRecv(can_frame *buf)
{
  if (CAN_MSGAVAIL == this->CAN->checkReceive())
  {
    this->CAN->readMsgBuf(&buf->can_id, &buf->can_dlc, buf->data);

    Serial.print("ID: 0x");
    Serial.print(buf->can_id, HEX);
    return 1;
  }

  return 0;
}

#endif /* !NVF_CAN_H_ */