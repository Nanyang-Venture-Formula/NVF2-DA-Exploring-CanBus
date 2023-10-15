
#include <Arduino.h>
#include <LiquidCrystal_I2C.h> 

#include "CanFD/NVF_Can.h"

#define CAN_CSN             10

MCP_CAN NVFCanI0(CAN_CSN);
NVF_Can NVFCan0(&NVFCanI0, 0xFF);

LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  Serial.begin(9600);
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
      Serial.print("Recieved CAN ID: 0x");
      Serial.print(rx_buf.can_id, HEX);
      Serial.print(", DLC: ");
      Serial.print(rx_buf.can_dlc);
      Serial.print(", Data: ");

      //lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(rx_buf.can_id, HEX);
      lcd.print(", DLC: ");
      lcd.print(rx_buf.can_dlc);
      lcd.print(", Data: ");

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