# RobotController
NodeMCU folder for the board code.
Android for the app.

The board open his own AP (SSID: "Roboto" Password: "RobotoPass"). The IP is now 10.10.10.1.

Default IP for the android app is 10.10.10.1, but you can change it on the fly.

## Parts needed:
* NodeMCU
* 3.3V Regulator
* Battery (We've used 6 AA batteries which gave us total of 7V)
* H Bridge
* 2 Engines
* Car body (have fun)

* Android device.

## Pinout:
### Motor Driver (H Bridge):
#### Left engine:
* Enable: GPIO14(D5) -> Motor-A Enable
* Forward: GPIO2(D4) -> IN3
* Backward: GPIO0(D3) -> IN4
#### Right engine:
* Enable: GPIO12(D6) -> Motor-B Enable
* Forward: GPIO15(D8) -> IN1
* Backward: GPIO13(D7) -> IN
### Proximity Sensor:
* Trigger: GPIO5(D1) -> Trigger
* Echo: GPI04(D2) -> Echo
