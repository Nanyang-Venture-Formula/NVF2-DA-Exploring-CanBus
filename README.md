# NVF2-DA-Exploring-CanBus

Some sample testing and debugging codes for CAN Bus Module MCP2515 with the following controllers:

- M5Stack Basic (Black) [ESP32 Based]
- WeAct Bluepill [STM32F103]
- WeAct Raspberry Pi Pico

## Current Status

This project is still a WIP. It does NOT work.

- The controllers will print "the message is sent successfully" but there is no other controller on the network that receieves the message. Hence being classified as false positives.
- The controller (only M5Stack) will print CAN Bus messages even though there is no controller transmitting anything, or as a matter of fact;  there having no other controller on the network.
