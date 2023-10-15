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

// #include <Arduino.h>
// #include "CanFD/NVF_Can.h"

// #define ANALOG_PIN          A0
// #define CAN_CSN             10
// #define DELAY_MS            250

// MCP_CAN NVFCanI0(CAN_CSN);
// NVF_Can NVFCan0(&NVFCanI0, 0x0F);

// void setup()
// {
//   Serial.begin(115200);
//   NVFCan0.setup();
//   pinMode(ANALOG_PIN, INPUT);
// }

// can_frame tx_buf;
// void loop()
// {
//   int reading = analogRead(ANALOG_PIN);
//   tx_buf.data[0] = (uint8_t) reading;

//   tx_buf.can_dlc = 1;
//   NVFCan0.tx(&tx_buf);
//   delay(DELAY_MS);   // send data per 100ms
// }

#include <Arduino.h>
#include "CanFD/NVF_Can.h"

#define ANALOG_PIN          A0
#define CAN_CSN             10
#define DELAY_MS            250

MCP_CAN NVFCanI0(CAN_CSN);
NVF_Can NVFCan0(&NVFCanI0, 0x456);

void setup()
{
  Serial.begin(9600);
  NVFCan0.setup();
  pinMode(ANALOG_PIN, INPUT);
}

can_frame tx_buf;

void loop()
{
  int reading = analogRead(ANALOG_PIN);
  tx_buf.data[0] = (uint8_t) reading;
  tx_buf.can_dlc = 1;

  //Serial Monitor
  Serial.print("Analog Reading: ");
  Serial.println(reading);

  if (NVFCan0.tx(&tx_buf))
  {
    Serial.println("CAN message sent successfully");
  }
  else
  {
    Serial.print("Error sending CAN message. Error Code:");
    // Serial.println(sendResult);
  }

  delay(DELAY_MS);   // send data per 100ms
}