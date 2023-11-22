#include "puits_lib.hpp"

lidar_t::lidar_t(){
    my_lidar = new LIDARLite_v3HP ;
} 
 
// lidar make measurement funciton
float lidar_t::make_measurement(){
    
    uint16_t distance_raw;
        
    my_lidar->waitForBusy();                  // 1. Wait
    my_lidar->takeRange();                    // 2. Trigger range measurement.
    my_lidar->waitForBusy();                  // 3. Wait for busyFlag to indicate device is idle. 
    
    distance_raw = my_lidar->readDistance();    // 4. Read new distance data from device registers
        
    dist = (float)distance_raw * 0.01 ;           // converts from [cm] to [m]

    return dist ;
}

float lidar_t::make_measurement_continous(){
    
    uint16_t distance_raw;
    
    if (my_lidar->getBusyFlag() == 0) {
        
        my_lidar->takeRange();    // Trigger the next range measurement

        distance_raw = my_lidar->readDistance();  // Read new distance data from device registers

        //dist = (float)distance_raw * 0.01 ;     // converts from [cm] to [m]
    
    }

    return distance_raw ;
   
}

void lidar_t::configure(){

    my_lidar->configure(1);  
    
    unsigned long time_now = millis() ;  

    // loop for 100ms
    while( millis() < (time_now + 100 ) ){
        make_measurement_continous() ;
    }
    
}

// default constructor
therm_ir_t::therm_ir_t(){
    
    my_therm_ir = new IRTherm ;
        
}

void therm_ir_t::configure(){

    bool status = my_therm_ir->begin() ;

    if( status == false ){              // error initing the sensor
        Serial.print("ERROR : therm_ir_t::configure \n" ) ;
    }

    my_therm_ir->setUnit(TEMP_C);       // set the library's units to Celsius
    
}

float therm_ir_t::make_measurement(){

    bool status = my_therm_ir->read() ;     // success -> 1, fail -> 0 
    
    if ( status ){ 

        ambient_temp = my_therm_ir->ambient() ;
        object_temp = my_therm_ir->object() ;
        
    }

    return object_temp ;
        
}


// default constructor
therm_cmos_t::therm_cmos_t(){
    my_therm_cmos = new DFRobot_SHT20(&Wire, SHT20_I2C_ADDR);
}

void therm_cmos_t::configure(){
    my_therm_cmos->initSHT20();
}

float therm_cmos_t::make_measurement(){
    
    ambient_temp = my_therm_cmos->readTemperature();    
    humidity = my_therm_cmos->readHumidity();           
       
    return ambient_temp ;
}

// default constructor
puit_t::puit_t(){

    //lidar = lidar_t();  
    //therm_ir_t ir_sensor ; 
    //therm_cmos_t cmos_sensor ; 
}

void puit_t::configure(){

    lidar.configure();
    ir_sensor.configure();
    cmos_sensor.configure();
}

void puit_t::make_measurement(){

    lidar.make_measurement();
    ir_sensor.make_measurement(); 
    cmos_sensor.make_measurement();   

}

void toggle_pin(int pin){
    
    static bool state = false ;
    
    if( state == false ){
        digitalWrite(pin, HIGH);
        state = true ;
    }
    else {
        digitalWrite(pin, LOW);
        state = false ; 
    }
    
}
