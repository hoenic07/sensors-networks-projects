# Brainstorming Sensor

## Sensors
* Flex
* Accelerometer: 4 Hz
* Light: 1 Hz
* Temperature: 0.2 Hz

## Situations

* Walking: Accelerometer
* Running: Accelerometer
* Standing: Accelerometer
* Sitting: Accelerometer
* Indoor / Outdoor: Temperature + Light
* Stuff put in or out: Flex + Light
* Backpack Open / closed: Light
* 

## Client
* Controls start and end of sending
* Collects and stores data of sensors
* Controls which sensors send data

## Protocol RAW data

* Command Overview:
    * ACK: 0x01
    * START_SAMPLING: 0x02
    * END_SAMPLING: 0x03
    * SET_ACTIVE_SENSORS: 0x04
    * SAMPLE: 0x05
    * SET_PARA: 0x06
    * REQ_PARA: 0x07
    * RESP_PARA: 0x08
* Message Format:
    * Start (1 Byte): 0x55
    * 
    * End (1 Byte): 0xAA
