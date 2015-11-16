#define GPBCON    (*((volatile unsigned long*)0x56000010))
#define GPBDAT    (*((volatile unsigned long*)0x56000014))

void led_init()
{
    GPBCON = (1<<10)|(1<<12)|(1<<14)|(1<<16);
    GPBDAT = 0xffffffff;
}

int led_on()
{
     GPBDAT = 0xa<<5; 	
}

void led_off()
{
    GPBDAT = 0xffffffff;	
}