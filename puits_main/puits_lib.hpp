#ifndef PUITS_LIB

#define PUITS_LIB

#include "Arduino.h"

#include "LIDARLite_v3HP.h"
#include "SparkFunMLX90614.h"
#include "DFRobot_SHT20.h"

#include <stdint.h>
#include <Wire.h>

// class for lidar distance sensor
class lidar_t {
        
    public: 

        LIDARLite_v3HP * my_lidar ;
        
        float dist ;                    // stores last distance measurement [m] 
        float dist_average ;
        
        lidar_t() ;                     // default constructor

        void configure();                     // inits the sensor
        
        float make_measurement() ;            // make measurement function
        float make_measurement_continous() ;  // make measurement continous function
      
} ;

// class for the IR temperature sensor (measure at a disance)
class therm_ir_t {

    public:

        IRTherm * my_therm_ir ;
        
        float ambient_temp ;            // stores last ambient temperature measurement [ºC] 
        float object_temp ;             // stores last 'object' temperature measurement [ºC] 

        float object_temp_average ;
        
        therm_ir_t() ;                  // default constructor

        void configure() ;              //
    
        float make_measurement() ;      // make measurement function
        float make_measurement_continous() ;      // make measurement function
        
} ;

// class for the CMOS temperature snesor (measure locally)
class therm_cmos_t {

    public:
        
        DFRobot_SHT20 * my_therm_cmos ;
        
        float ambient_temp ;            // stores last ambient temperature measurement [ºC] 
        float ambient_temp_average ;
        
        float humidity ;                // stores last humidity measurement [%] 

        therm_cmos_t() ;                // default constructor

        void configure() ;
        
        float make_measurement() ;      // make measurement function
        float make_measurement_continous() ;      // make measurement function
} ;

class puit_t{
    
    public:

        lidar_t lidar ; 
        therm_ir_t ir_sensor ; 
        therm_cmos_t cmos_sensor ; 

        puit_t( );
        
        void configure();

        void make_measurement();
} ;

void toggle_pin(int pin);

#endif
