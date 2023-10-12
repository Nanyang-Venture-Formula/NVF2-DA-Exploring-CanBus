# 1. NVF2-DA-Exploring-CanBus

Some sample testing and debugging codes for CAN Bus Module MCP2515 with the following controllers:

| Controller                          | Status |
|-------------------------------------|:------:|
| Arduino UNO                         |   ✅    |
| M5Stack Basic (Black) [ESP32 Based] |   ❌    |
| WeAct Bluepill [STM32F103]          |   ❌    |
| WeAct Raspberry Pi Pico             |   ❌    |

## 1.1. Current Status

This project is still a WIP.

- For `Arduino UNO`, code has been tested and is working.
- For the `other controllers`, there are multiple SPI interfaces as well as multiple pins muxed into single SPI buses. it is not yet known to us on how we will be able to choose the SPI pins on the other boards.

## Examples

Apart from bare bones `tx` and `rx` examples for using NVF_CAN wrappers, we also have examples for:

| Example                                                      |   Status   |
|--------------------------------------------------------------|:----------:|
| [CAN RX -> LCD](./NVF2-CanFD/examples/main_rx_lcd.cpp)       | Not tested |
| [Counter -> CAN TX](./NVF2-CanFD/examples/main_tx.cpp)       | Not tested |
| [Analog -> CAN TX](./NVF2-CanFD/examples/main_tx_analog.cpp) | Not tested |
