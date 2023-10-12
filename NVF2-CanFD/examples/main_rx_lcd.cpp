/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Exploring-CanBus
** File description:
** main_rx
*/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h> 

#define CAN_CSN             10

// include Serial Before NVF_Can to override Serial to SerialUSB
#include "CanFD/NVF_Can.h"

MCP_CAN NVFCanI0(CAN_CSN);
NVF_Can NVFCan0(&NVFCanI0, 0x01);

void setup()
{
  Serial.begin(115200);
  NVFCan0.setup();

  lcd.init();
  lcd.clear();         
  lcd.backlight();     
  lcd.setCursor(0, 0);
  lcd.print("NVF 2");
}

can_frame rx_buf;

void loop()
{
  if (NVFCan0.taskLoopRecv(&rx_buf))
  {
      Serial.print(rx_buf.can_id, HEX);
      Serial.print(": ");
      Serial.print(rx_buf.can_dlc);
      Serial.print("->");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(rx_buf.can_id, HEX);
      lcd.print(": ");
      lcd.print(rx_buf.can_dlc);
      lcd.print("->");

    for (int i = 0; i < rx_buf.can_dlc; i++)
    {
      Serial.print(rx_buf.data[i], HEX);
      Serial.print(" ");
      lcd.print(rx_buf.data[i], HEX);
      lcd.print(" ");
    }
    Serial.println();
    lcd.print("&");
  }
}