# ArduinoServoManager
## What's this? 
This project is servo motor manager for Arduino with PCA9685.
- Send json message by serial communication like `{"servo0": 90.5, "servo1":80.0}`.
- Limit servo angle by software control.


## How to use
1. install PlatformIO.
1. Open this project in PlatfromIO.
1. Connect PC and Arduino.
1. Run build and install.
1. Send json message from any application which can use serial communication(e.g. Serial Monitor, PySerial, ...).

## How to increase motors
- Default max servo numbers are 3.
- You can add servos up to 16(which is max numbers or PCA9685).
- Copy and paste line *0~*2, and change numbers `main.cpp`(I wrote variables for 3 motors directly for saving memory).

(If you want to decrease motors, simply send json without unused number).