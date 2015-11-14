#define GPBCON (volatile unsigned long*)0x56000010
#define GPBDAT (volatile unsigned long*)0x56000014

int led_init()
{
    *(GPBCON) = (1<<10)|(1<<12)|(1<<14)|(1<<16);
    *(GPBDAT) = 0xa<<5;
    return 0;     
}


