# miniboot
bootloader for mini2440 development board
functions described will be provided: 
1. set exception vectors 
2. set svc32 mode 
3. turn off watchdog
4. mask all irqs
5. initialize clock
6. disable MMU and I/D caches
7. initialize memory controler
8. initialize stack section
9. clear bss sector
10. jump to c function
11. initialize nand flash controler
12. download bootloader to sdram from nand flash
13. initialize MMU 
14. initialize serial port
15. initialize Ethernet card
16. initialize LCD
17. initialize touch screen
18. wait for and execute command lines

