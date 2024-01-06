// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

SoftwareSerial XBee(2, 3); // RX, TX

void setup()
{
    XBee.begin(9600);
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available()) {       // If data comes in from serial monitor, send it out to XBee
        XBee.write(Serial.read());
    }
    if (XBee.available()) {         // If data comes in from XBee, send it out to serial monitor
        Serial.write(XBee.read());
    }
}
