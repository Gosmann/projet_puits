#include "puits_lib.hpp"

lidar_t::lidar_t(){
    my_lidar = new LIDARLite_v3HP ;
} 
 
float lidar_t::make_measurement_continous(){
    
    uint16_t distance_raw;

    while( my_lidar->getBusyFlag() != 0 ){
        
    }

    if (my_lidar->getBusyFlag() == 0) {
        
        my_lidar->takeRange();    // Trigger the next range measurement

        distance_raw = my_lidar->readDistance();  // Read new distance data from device registers

        dist = (float)distance_raw * 0.01 ;     // converts from [cm] to [m]
        
        dist_average = dist * 0.1 + dist_average * 0.9 ;
    }

    return dist_average ;
   
}

// lidar make measurement funciton
float lidar_t::make_measurement(){
    
    uint16_t distance_raw;

    unsigned long time_now = millis() ;  
    
    // loop for 30ms
    while( millis() < (time_now + 30 ) ){
        //make_measurement_continous() ;
        my_lidar->takeRange();    // Trigger the next range measurement
    }
    
    my_lidar->waitForBusy();                  // 1. Wait
    my_lidar->takeRange();                    // 2. Trigger range measurement.
    my_lidar->waitForBusy();                  // 3. Wait for busyFlag to indicate device is idle. 
    
    distance_raw = my_lidar->readDistance();    // 4. Read new distance data from device registers
        
    dist = (float)distance_raw * 0.01 ;           // converts from [cm] to [m]

    dist_average = dist ;
    
    return dist ;
}

void lidar_t::configure(){

    my_lidar->configure(0);  
    
    unsigned long time_now = millis() ;  

    // loop for 100ms
    while( millis() < (time_now + 1000 ) ){
        make_measurement_continous() ;
        //my_lidar->takeRange();    // Trigger the next range measurement
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

    object_temp_average = make_measurement() ;
}

float therm_ir_t::make_measurement(){

    bool status = my_therm_ir->read() ;     // success -> 1, fail -> 0 
        
    if ( status ){ 

        ambient_temp = my_therm_ir->ambient() ;
        object_temp = my_therm_ir->object() ;
    }

    object_temp_average = object_temp ;
    
    return object_temp ;
        
}

float therm_ir_t::make_measurement_continous(){
    
    bool status = my_therm_ir->read() ;     // success -> 1, fail -> 0 
    
    while ( my_therm_ir->read() != 1 ){ 

    }
    
    //ambient_temp = my_therm_ir->ambient() ;
    object_temp = my_therm_ir->object() ;

    //Serial.println(object_temp);
    
    object_temp_average = object_temp * 0.01 + object_temp_average * 0.99 ;
    

    return object_temp_average ;

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

    ambient_temp_average = ambient_temp ;
    
    return ambient_temp ;
}

float therm_cmos_t::make_measurement_continous(){
    
    ambient_temp = my_therm_cmos->readTemperature();    
    humidity = my_therm_cmos->readHumidity();           

    ambient_temp_average = ambient_temp ;
    
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
    int i;

    lidar.make_measurement();
    ir_sensor.make_measurement() ; 
    cmos_sensor.make_measurement() ;   
    
    for(i = 0 ; i < 10 ; i++)    
        lidar.make_measurement_continous() ;

    //Serial.print("end lidar \n") ;
    
    for(i = 0 ; i < 10 ; i++) {   
        ir_sensor.make_measurement_continous() ; 
        delay(100);
    }    
    //Serial.print("end IR \n") ;
    for(i = 0 ; i < 1 ; i++)    
        cmos_sensor.make_measurement_continous() ; 

    //Serial.print("end cmos \n") ;

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
