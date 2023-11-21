/*!
 * @file  getHumidityAndTemperature.ino
 * @brief  DFRobot's SHT20 Humidity And Temperature Sensor Module
 * @details  This example demonstrates how to read the user registers to display resolution and other settings.
 * @n  Uses the SHT20 library to display the current humidity and temperature.
 * @n  Open serial monitor at 9600 baud to see readings.
 * @n  Errors 998 if not sensor is detected. Error 999 if CRC is bad.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [Zhangjiawei](jiawei.zhang@dfrobot.com)
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2021-12-03
 * @url  https://github.com/DFRobot/DFRobot_SHT20
 */
#include "DFRobot_SHT20.h"

/**
 * Hardware Connections:
 * -VCC = 3.3V
 * -GND = GND
 * -SDA = A4 (use inline 330 ohm resistor if your board is 5V)
 * -SCL = A5 (use inline 330 ohm resistor if your board is 5V)
 */
DFRobot_SHT20 sht20(&Wire, SHT20_I2C_ADDR);

void setup()
{
  Serial.begin(115200);

  // Init SHT20 Sensor
  sht20.initSHT20();
  
  /**
   * Check the current status information of SHT20
   * Status information: End of battery, Heater enabled, Disable OTP reload
   * Check result: yes, no
   */
  // no need for this 
  //sht20.checkSHT20(); 
}

void loop()
{
    char buffer [100] ;
    
    float humid = sht20.readHumidity();          //  Read the measured data of air humidity
    float temp = sht20.readTemperature();        //  Read the measured temp data
    
    sprintf(buffer, "ambient temp [%3.2f]ºC | humidity [%3.2f]%% \n", temp, humid ) ;
        
    Serial.print( buffer ) ;
    
    delay(1000);
}
