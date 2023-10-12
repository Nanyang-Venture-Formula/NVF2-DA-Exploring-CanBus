/**
 * @file NVF_Can.cpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 12-10-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "NVF_Can.h"

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
