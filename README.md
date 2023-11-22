# projet_puits

## important mods for compilation

### sprintf
for sprintf change the file :

~/.arduino15/packages/arduino/hardware/avr/1.8.6/platform.txt

with the following flags :

compiler.c.extra_flags= -Wl,-u,vfprintf -lprintf_flt -lm   -Wl,-u,vfscanf -lscanf_flt -lm
compiler.c.elf.extra_flags= -Wl,-u,vfprintf -lprintf_flt -lm   -Wl,-u,vfscanf -lscanf_flt -lm

### libraries
add library directories to the director : 

~/Arduino/libraries

the library directories are :

DFRobot_SHT20 
LIDARLite_Arduino_Library
SparkFun_MLX90614_Arduino_Library-master

these libraries are located at this repository at:

./references_libraries_originals





