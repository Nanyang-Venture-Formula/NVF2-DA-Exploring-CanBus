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
#include "CanBus/NVF_Can.h"

<<<<<<< HEAD:NVF2-CanFD/examples/main_tx_analog.cpp
#define ANALOG_PIN          A0
#define CAN_CSN             10
#define DELAY_MS            1000
=======
#define DELAY_MS            250
>>>>>>> 7792aa9d91ee6d9d2a100b49dcd00acb9cf7a217:NVF2-Can/examples/main_tx_analog.cpp

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
