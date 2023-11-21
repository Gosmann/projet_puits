/****************************************************************************** 
MLX90614_Serial_Demo.ino
Serial output example for the MLX90614 Infrared Thermometer

This example reads from the MLX90614 and prints out ambient and object 
temperatures every half-second or so. Open the serial monitor and set the
baud rate to 9600.

Hardware Hookup (if you're not using the eval board):
MLX90614 ------------- Arduino
  VDD ------------------ 3.3V
  VSS ------------------ GND
  SDA ------------------ SDA (A4 on older boards)
  SCL ------------------ SCL (A5 on older boards)
  
An LED can be attached to pin 8 to monitor for any read errors.

Jim Lindblom @ SparkFun Electronics
October 23, 2015
https://github.com/sparkfun/SparkFun_MLX90614_Arduino_Library

Development environment specifics:
Arduino 1.6.5
SparkFun IR Thermometer Evaluation Board - MLX90614
******************************************************************************/

/*

for sprintf change the file :

~/.arduino15/packages/arduino/hardware/avr/1.8.6/platform.txt

with the following flags :

compiler.c.extra_flags= -Wl,-u,vfprintf -lprintf_flt -lm   -Wl,-u,vfscanf -lscanf_flt -lm
compiler.c.elf.extra_flags= -Wl,-u,vfprintf -lprintf_flt -lm   -Wl,-u,vfscanf -lscanf_flt -lm

*/

#include <Wire.h>       // I2C library, required for MLX90614
#include <stdio.h>      // sprintf

//#include <SparkFunMLX90614.h> //Click here to get the library: http://librarymanager/All#Qwiic_IR_Thermometer by SparkFun
#include "./SparkFunMLX90614.h"

IRTherm therm; // Create an IRTherm object to interact with throughout

void setup() 
{
  Serial.begin(115200); // Initialize Serial to log output
  Wire.begin(); //Joing I2C bus
  
  if (therm.begin() == false){ // Initialize thermal IR sensor
    Serial.println("Qwiic IR thermometer did not acknowledge! Freezing!");
    while(1);
  }
  Serial.println("Qwiic IR Thermometer did acknowledge.");
  
  therm.setUnit(TEMP_C); // Set the library's units to Celsius
  // Alternatively, TEMP_F can be replaced with TEMP_C for Celsius or
  // TEMP_K for Kelvin.
  
  pinMode(LED_BUILTIN, OUTPUT); // LED pin as output
}

void loop() 
{
    char buffer [100] ;
    
    digitalWrite(LED_BUILTIN, HIGH);
    
    // Call therm.read() to read object and ambient temperatures from the sensor.
    if (therm.read()){ // On success, read() will return 1, on fail 0.
    
        // Use the object() and ambient() functions to grab the object and ambient temperatures.
        // They'll be floats, calculated out to the unit you set with setUnit().
        
        sprintf(buffer, "objtec temp [%3.2f]ºC | ambient temp [%3.2f]ºC", therm.object(), therm.ambient() ) ;
        
        Serial.println( buffer ) ;  
    }
    
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    
}
