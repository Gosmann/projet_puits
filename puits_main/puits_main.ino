#include "puits_lib.hpp"
#include <SoftwareSerial.h>

puit_t puit ;
SoftwareSerial XBee(2, 3);          // rx, tx

char buffer[256];
char command[128];

// put your setup code here, to run once:
void setup() {

    pinMode(13, OUTPUT);
    
    // hardware setup
    XBee.begin(9600);
    Serial.begin(9600);
    Wire.begin();
    
    // library setup
    puit.configure();
}

// put your main code here, to run repeatedly:
void loop() {
    unsigned long time_now = millis() ; 
     
    puit.make_measurement() ;

    // essentials
    /*
    sprintf(buffer, "lidar_distance: [% 2.2f]m | ir_sensor: [%2.2f]ºC | cmos_sensor: [%2.2f]ºC \n",
        puit.lidar.dist, puit.ir_sensor.object_temp, puit.cmos_sensor.ambient_temp) ;
    */
    
    sprintf(buffer, "{ \"lidar_distance\" : % 2.2f , \"ir_sensor\" : %2.1f , \"cmos_sensor\" : %2.1f } \n",
        puit.lidar.dist_average, puit.ir_sensor.object_temp_average, puit.cmos_sensor.ambient_temp_average) ;
    
    //sprintf(buffer, " % 2.2f , % 2.2f , % 2.2f \n",
    //    puit.lidar.dist_average, puit.ir_sensor.object_temp_average, puit.cmos_sensor.ambient_temp_average) ;
    
    
    // full
    //sprintf(buffer, "lidar_distance: [% 2.2f]m | ir_sensor(obj): [%2.2f]ºC | ir_sensor(amb): [%2.2f]ºC | cmos_sensor(amb): [%2.2f]ºC | cmos_sensor(hum): [% 3.2f]%% \n",
    //    puit.lidar.dist, puit.ir_sensor.object_temp, puit.ir_sensor.ambient_temp, puit.cmos_sensor.ambient_temp, puit.cmos_sensor.humidity) ;
    //Serial.print(buffer) ;
    //XBee.write(buffer) ;
    
    toggle_pin(13);

    int aux = 0;
    while( millis() < (time_now + 5000 ) ){
        /*
        if (Serial.available()) {       // If data comes in from serial monitor, send it out to XBee
            XBee.write(Serial.read());
        }
        
        // gets commands from computer (raspberry pi)
        if (XBee.available()) {         
            
            //Serial.print( XBee.read() ) ;
            
            command[0] = XBee.read();
            
            //Serial.write( command[0] );
            //Serial.write( '\n' );

            if(command[0] == 'm'){
                Serial.print(buffer) ;
                XBee.write(buffer) ;
            }
        */
        if( aux == 0){
            Serial.print(buffer) ;
            XBee.write(buffer) ;      
            aux = 1;
        }
            
    }
}
