* Resource Link : [Click Here](https://www.spiceworks.com/tech/hardware/articles/what-is-rtos/  )
## Real Time Operating System
* Resource : [Click Here](https://www.freertos.org/Documentation/00-Overview)
* Video Tutorial : [Click Here](https://www.youtube.com/watch?v=F321087yYy4&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz)
* Advantage and disadvantage : [click here](https://www.nabto.com/rtos-versus-os-advantages-disadvantages/)
## Important Terms
* Task - Set of Program instruction loaded in memory
* Thread - Unit of CPU and it has own stack and counter
* Process - Instance of Computer Program

13th January 9:30 - 11:30
### GPOS(General Purpose Operating System)
* It is used to have basic usage and easily be interpreted by human beings
* It is mainly do three operations
    * Resource management - Manage hardware resource like CPU,RAM,I/O Device and allocate resource when the application needed
    * Task Scheduling - Havinng scheduling algorithm to mannage the multiple process (SJF,FCFS,RR)
    * Device Driver - Allow system to read and write from the external disc - printer
    * eg : windows,macos,linux,android  and ios
#### Disadvantage of GPOS
* It is not well suited for real time constraints which leads to higher latency
* Here the scheduler is non deterministic like when we have some deadline for some tasks to do , it won't follow and do it as it is . So this is the disadvantage and we use RTOS
* It is unsuitable for critical operations

### RTOS
* It is deterministic
* It provide high level device driver
* It is mainly used when we do concurrent task and have deadline for the task
* It has specially written scheduling algorithms
* used in shipping stations automatic emergency brake
* Super loop : A super loop is a simple program structure where tasks are executed sequentially in an infinite loop.   
    * It continuously checks and performs each task, one after the other, without any prioritization 
    * Super loops are efficient for small systems but may delay critical tasks in more complex applications.
    * It is not applicable in real time , for example we have temperatore monitoring system , in which first it reads the value throught the sensor and then print the value and turn on if the temperature is greater than 40 . All these must me happen in sequential manner and each tasks takes some time . What if i add a new funtion that add record on the log which place after the print task . So that this will take time to do so our operation maybe get affected . So that we need concurrency which RTOS have
* Advantages : 
    * Priority Task Scheduling
    * Reliability - It will finish the process on time
    * Efficiency - It requires less memory
    * Cross-Platform Support
* Disadvantages : 
    * Longer wait for low priority task
    * It is good at scheduling the small number of tasks , but it is not good at multitaskingx