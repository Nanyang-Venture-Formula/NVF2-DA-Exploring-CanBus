/**
 * @file main_tx_analog.cpp
 * @author SCOTT CJX
 * @brief 
 * @version 0.1
 * @date 2023-10-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include "CanFD/NVF_Can.h"

#define ANALOG_PIN          A0
#define CAN_CSN             10
#define DELAY_MS            250

MCP_CAN NVFCanI0(CAN_CSN);
NVF_Can NVFCan0(&NVFCanI0, 0x0B);

void setup()
{
  Serial.begin(115200);
  NVFCan0.setup();
  pinMode(ANALOG_PIN, INPUT);
}

can_frame tx_buf;
void loop()
{
  int reading = analogRead(ANALOG_PIN);
  Serial.println(reading);
  tx_buf.data[0] = (uint8_t) reading;
  Serial.println(tx_buf.data[0]);

  tx_buf.can_dlc = 1;
  NVFCan0.tx(&tx_buf);
  delay(DELAY_MS);   // send data per 100ms
}