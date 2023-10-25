# Technical Documentation

This document outlines the technical aspects to the Exporing-CanBus codes.

## Board Selection/ Configurations

Board definitions for this project are stored in [`board_dfs.h`](../NVF2-Can/examples/board_dfs.h). Refer to/edit this document to achieve the correct hookup.

### SPI Bus and Pins Selection

Apart from Arduino UNO/ Nano boards, more powerful boards such as [raspberry pi pico](/) and [bluepill](/) have mulitple SPI Busses and pins for these SPI Busses. We should first define the pins and SPI Bus we want the controller to use.

The constructor for SPI bus (ArduinoCore's Mbed API): `arduino::MbedSPI SPI {miso, mosi, sck}`

This Should not be present for boards that do not have more than 1 SPI Bus/ Pin bank for SPI. It may also not be the correct constructor for all Boards. For now this works for us...


