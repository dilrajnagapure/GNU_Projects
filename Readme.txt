1. Download and Install GNU compiler and debugger, OpenOCD, makefile
2. Follow this link for instructions:
   https://www.youtube.com/watch?v=AzYC5hO2uJk&list=PLERTijJOmYrDiiWd10iRHY0VRHdJwUH4g&index=7
3. Commands on terminal 1:
   Open project location and open terminal 1
   make clear
   make semi  // Build code which uses semihosting feature
   make load  // run host program OpenOCD   
   
   Open another terminal at the same project location:
   arm-none-eabi-gdb.exe
   target remote localhost:3333
   monitor reset init                            //gdb init
   monitor flash write_image erase final_sh.elf  //flash the mcu with code
   monitor reset halt                            // it shall print pc, msp values
   monitor resume                                //Green led shall start blinking
   
4. Also follow GNU gdb command page for more information