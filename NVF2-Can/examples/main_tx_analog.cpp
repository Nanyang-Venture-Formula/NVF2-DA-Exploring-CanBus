/**
 * @file main_tx_analog.cpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 16-10-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include <SPI.h>

#include "board_dfs.h"
#include "NVF_Can.h"

#define DELAY_MS            250

MCP_CAN NVFCanI0(CAN_CSN);
NVF_Can NVFCan0(&NVFCanI0, 0x0B);

can_frame tx_buf;

can_frame tx_buf;

void setup()
{
  Serial.begin(115200);
  NVFCan0.setup();
  pinMode(ANALOG_PIN, INPUT);
}

void loop()
{
  int reading = analogRead(ANALOG_PIN);
  tx_buf.data[0] = (uint8_t) map(reading, 0, 1023, 0, 0xFF);
  tx_buf.data[2] = (uint8_t) reading & 0xFF;
  tx_buf.data[1] = (uint8_t) (reading >> 8) & 0xFF;

  tx_buf.can_dlc = 3;

  //Serial Monitor
  Serial.print("Analog Reading: ");
  Serial.println(reading);

  if (NVFCan0.tx(&tx_buf))
  {
    Serial.println("CAN message sent successfully");
  }
  else
  {
    Serial.println("Error sending CAN message");
  }

  delay(DELAY_MS);   // send data per 100ms
}
