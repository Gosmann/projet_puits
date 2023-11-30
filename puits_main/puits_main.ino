#include "puits_lib.hpp"

puit_t puit ;

char buffer[256];

// put your setup code here, to run once:
void setup() {

    pinMode(13, OUTPUT);
    
    // hardware setup
    Serial.begin(115200);
    Wire.begin();
    
    // library setup
    puit.configure();
}

// put your main code here, to run repeatedly:
void loop() {
    
    puit.make_measurement() ;

    // essentials
    /*
    sprintf(buffer, "lidar_distance: [% 2.2f]m | ir_sensor: [%2.2f]ºC | cmos_sensor: [%2.2f]ºC \n",
        puit.lidar.dist, puit.ir_sensor.object_temp, puit.cmos_sensor.ambient_temp) ;
    */
    
    sprintf(buffer, "{ \"lidar_distance\" : % 2.2f , \"ir_sensor\" : %2.2f , \"cmos_sensor\" : %2.2f } \n ",
        puit.lidar.dist, puit.ir_sensor.object_temp, puit.cmos_sensor.ambient_temp) ;
    
    
    
    // full
    //sprintf(buffer, "lidar_distance: [% 2.2f]m | ir_sensor(obj): [%2.2f]ºC | ir_sensor(amb): [%2.2f]ºC | cmos_sensor(amb): [%2.2f]ºC | cmos_sensor(hum): [% 3.2f]%% \n",
    //    puit.lidar.dist, puit.ir_sensor.object_temp, puit.ir_sensor.ambient_temp, puit.cmos_sensor.ambient_temp, puit.cmos_sensor.humidity) ;
    
    Serial.print(buffer) ;

    toggle_pin(13);
    delay(500);
}
