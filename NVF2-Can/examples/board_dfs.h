/**
 * @file board_dfs.h
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 16-10-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include <Arduino.h>

namespace BoardDef
{
    #ifdef BOARD_UNO
    // Tested Working
    #define CAN_CSN             10
    #define CAN_CSN2             9
    #define ANALOG_PIN          A0
    #endif
    
    #ifdef BOARD_BLUEPILL
    // Tested Working
    //                          (arduino::MbedSPI) {miso, mosi, sck}
    #define SPI                 (arduino::MbedSPI) {PA7, PA6, PA5}
    #define CAN_CSN             PA4
    #define CAN_CSN2            PA3
    #define ANALOG_PIN          PA0
    #endif

    #ifdef BOARD_PICO
    // WIP
    //                          (arduino::MbedSPI) {rx, tx, sck}
    #define SPI                 (arduino::MbedSPI) {3, 4, 2}
    #define CAN_CSN             5
    #define CAN_CSN             6
    #define Serial              SerialUSB
    #define ANALOG_PIN          10
    #endif
};

