* CPU - Execute program / code , when the power is applite the CPU becom hunger to execute  the code from the storage device(RAM,ROM)
* Computer memory is organised as a array of intereger called bytes and each byte contain 0-255 value
* ROM - Contain pre programmed code and do only read operation
* RAM - Temporary code and do both read and write operation
* DIMM (Dual In-Line Memory Module) chip is RAM
* BIOS (Basic Input/Output System) chip is ROM 
* CPU and ROM are connected through Address BUS
* The Address bus is unidirectional which means the CPU address pins are Outputs and ROM pin address are inputs
![alt text](image100.png)
* We have both read and write operation to indicate that we have address bus and both of them are **actively low** (have bar) and they are mutually exclusive 
* The reason for the active low od RD/WR is power consumption
* Data bus is used to transfer  the data and it is Bidirectional and it carries 8 bit of data
![alt text](image-1101.png)
![alt text](image-15.png)
* The firmware instruction (os code) is located on the starting address 
![alt text](image-16.png)
* Any HEX number that is above 8000 is used by RAM and below 8000 is used by ROM,because the forst address is access by the firmware . So the A15 decide which need to acticate (1 means RAM and 0 means ROM) eg. 0000 0000 0000 0000 - ROM, 1000 0000 0000 0000 - RAM
* 4 bits - Nibble
* 8 bits - byte
* 16 bits - Word
* Z - state - It is disconnected
