

#define  ADCCON        (*((volatile unsigned long*)0x58000000)) 
#define  ADCTSC        (*((volatile unsigned long*)0x58000004))
#define  ADCDAT0       (*((volatile unsigned long*)0x5800000c))
#define  ADCDAT1       (*((volatile unsigned long*)0x58000010))

#define  SRCPND        (*((volatile unsigned long*)0x4a000000)) 
#define  INTMSK        (*((volatile unsigned long*)0x4a000008)) 
#define  INTPND        (*((volatile unsigned long*)0x4a000010))
#define  INTSUBMSK     (*((volatile unsigned long*)0x4a00001c))
#define  SUBSRCPND     (*((volatile unsigned long*)0x4a000018)) 

int xdata, ydata;

void ts_init()
{
    ADCCON = (1<<14)|(49<<6);
    
    INTMSK &=~(1<<31);  
    INTSUBMSK &=~(1<<9);
    
    ADCTSC = 0xd3;   
	
}


void tc_handler()
{
    /**启动xy坐标自动转换**/
    ADCTSC = (1<<2); 
    ADCCON |=(1<<0);
    
    /**等待转换完成**/
    while(!(ADCCON&(1<<15)));
    
    /**获取坐标**/
    xdata = ADCDAT0 & 0x3ff;
    ydata = ADCDAT1 & 0x3ff;
    /**清除按下中断**/
    SUBSRCPND |= (1<<9);
    SRCPND |=(1<<31);
    INTPND |=(1<<31);
       
    /**进入等待弹起中断**/
    ADCTSC = 0xd3;
    ADCTSC |= (1<<8);
    
    while(1)
    {
        if(SUBSRCPND&(1<<9))
             break;
    }
    /**清除弹起中断**/
    SUBSRCPND |= (1<<9);
    SRCPND |=(1<<31);
    INTPND |=(1<<31);
    printf("x= %d,y= %d\n",xdata,ydata);
    /**再次进入等待按下中断的状态**/
    ADCTSC = 0xd3;
    	
}