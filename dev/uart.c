#define GPHCON      (*((volatile unsigned long *)0x56000070))

#define INTMSK      (*((volatile unsigned long *)0x4a000008))
#define INTSUBMSK   (*((volatile unsigned long *)0x4a00001c))
#define SUBSRCPND   (*((volatile unsigned long *)0x4a000018))

#define ULCON0      (*((volatile unsigned char *)0x50000000))
#define UCON0       (*((volatile unsigned long *)0x50000004))
#define UTRSTAT0    (*((volatile unsigned char *)0x50000010))
#define UBRDIV0     (*((volatile unsigned char *)0x50000028))
#define UTXH0       (*((volatile unsigned char *)0x50000020))
#define URXH0       (*((volatile unsigned char *)0x50000024))

void port_init()
{
    GPHCON &= ~(0xf<<4);	
    GPHCON |= (0xa<<4); 
}

void irq_init()
{
    INTMSK &=~ (1<<28);
    INTSUBMSK &= ~((1<<0)|(1<<1));
}

void uart_con_init()
{
    /**8-bits word length ;1 stop bit ; none parity **/
    ULCON0 = (3<<0)|(0<<2)|(0<<3)|(0<<6);	
    
    /**Tx Rx Mode: polling mode; Clock for the baud rate is PCLK**/
    UCON0 = 0b1001;
    
    /**Baud rate is 115200 bps PCLK = 50M***/
    UBRDIV0 = (int)(50000000/(115200*16)-1);
}
void uart_init()
{
    port_init();
    
 //   irq_init();
     
    uart_con_init();    	
}



void putc(unsigned char ch)
{
    while(!(UTRSTAT0&(1<<2)));	
        UTXH0 = ch;
}

unsigned char getc(void)
{
    unsigned char ret = 0;
    while(!(UTRSTAT0&(1<<0)));	
       ret = URXH0;    
	if ( (ret == 0x0d) || (ret == 0x0a) )
	{
	    putc(0x0d);
	    putc(0x0a);	
	}      	
	else
	    putc(ret);
	    
        return ret;
}

void display_menul()
{
    int cmm_num = 0;
    printf("\n******************************************\n\r");
    printf("\n********** miniboot by Linzi *************\n\r");
    printf("[1].Download Linux Kernel from TFTP Server!\n\r");
    printf("[2].Boot Linux Kernel from RAM!\n\r");
    printf("[3].Boot Linux Kernel from Nand Flash!\n\r");
    printf("\nPlease Select:");
} 
