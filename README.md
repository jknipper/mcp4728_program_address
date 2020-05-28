# MCP4728 program address

This is a working solution to program MCP4728 DAC i2c address. It was tested with an Arduino Nano and a Teensy 3.2 but should work with other boards. Just change pins accordingly.

## Requirements
For bit banging the new addesss `SoftI2cMaster` library from https://github.com/TrippyLighting/SoftI2cMaster is needed.

## Wiring
Wire up `SDA`, `SCL`, `LDAC`, `VDD` and ground pin of the DAC to your development board. A pull-up resistor might be needed for `SDA` and `SCL`.

You can verify the success of programming with `i2c_scanner` from https://playground.arduino.cc/Main/I2cScanner

## See also
http://ww1.microchip.com/downloads/en/DeviceDoc/22187E.pdf

https://www.microchip.com/forums/m1139524.aspx

https://forum.pjrc.com/threads/28424-Programming-the-I2C-address-of-a-MCP4728-4-channel-DAC-using-i2c_t3
