/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** NVF_Can
*/

#ifndef NVF_CAN_H_
#define NVF_CAN_H_

#include <Arduino.h>
#include "mcp_can.h"
#include <SPI.h>
#include "stdint.h"

class NVF_Can : MCP_CAN
{
public:
  long unsigned int canId;
  using MCP_CAN::MCP_CAN;

  void taskSetup(void);
  // void attachRecvInterrupt(uint8_t);
  void taskLoopRecv(void);
  bool taskLoopSend(byte *, uint);
};

// void cb()
// {
//   Serial.println("Interrupted --> ");
// }

// void attachRecvInterrupt(uint8_t intPin)
// {
//   attachInterrupt(intPin, cb, PinStatus::FALLING);
// }

bool NVF_Can::taskLoopSend(byte *data, uint len)
{
  byte sndStat = this->sendMsgBuf(this->canId, 0, len, data);

  if (sndStat == CAN_OK)
  {
    Serial.println("Message Sent Successfully!");
    return 1;
  }
  else
  {
    Serial.println("Error Sending Message...");
    return 0;
  }
}

void NVF_Can::taskLoopRecv(void)
{
  unsigned char len = 8;
  unsigned char buf[8];
  unsigned long txCanId = 0;

  uint8_t msgStatus = this->checkReceive();
  if (msgStatus == CAN_MSGAVAIL)
  {
    this->readMsgBuf(&txCanId, &len, buf);
    // txCanId = this->getCanId();
    Serial.println("-----------------------------");
    Serial.print("Get data from ID: ");
    // Serial.println(txCanId, HEX);

    for (int i = 0; i < len; i++) // print the data
    {
      Serial.print(buf[i], HEX);
      Serial.print("\t");
    }
    Serial.println();
  }
  else if (msgStatus == CAN_NOMSG)
  {
    Serial.println("CAN_NOMSG");
  }
}

void NVF_Can::taskSetup(void)
{
  if (this->begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
  {
    Serial.println("MCP2515 Initialized Successfully!");
  }
  else
  {
    Serial.println("Error Initializing MCP2515...");
  }

  this->setMode(MCP_NORMAL); // Change to normal mode to allow messages to be transmitted
}

#endif /* !NVF_CAN_H_ */