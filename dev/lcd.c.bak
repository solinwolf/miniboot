
#define GPCCON      (*((volatile unsigned long*)0x56000020))
#define GPDCON      (*((volatile unsigned long*)0x56000030))
#define GPGCON      (*((volatile unsigned long*)0x56000060))
#define LCDCON1     (*((volatile unsigned long*)0x4D000000))
#define LCDCON2     (*((volatile unsigned long*)0x4D000004))
#define LCDCON3     (*((volatile unsigned long*)0x4D000008))
#define LCDCON4     (*((volatile unsigned long*)0x4D00000C))
#define LCDCON5     (*((volatile unsigned long*)0x4D000010))

#define LCDSADDR1   (*((volatile unsigned long*)0x4D000014))
#define LCDSADDR2   (*((volatile unsigned long*)0x4D000018))
#define LCDSADDR3   (*((volatile unsigned long*)0x4D00001C))
#define TPAL        (*((volatile unsigned long*)0x4D000050))


#define VSPW      9
#define VBPD      2
#define LINEVAL   239  //320*240
#define VFPD      1
#define CLKVAL    6 
#define HSPW      1
#define HBPD      5
#define HOZVAL    319
#define HFPD      0xc

unsigned short frame[240][320];

void lcd_port_init()
{
    GPCCON = 0xaaaaaaaa;
    GPDCON = 0xaaaaaaaa;
}


void lcd_timing_init()
{
    LCDCON1 = (CLKVAL<<8)|(0x3<<5)|(0xc<<1)|(0<<0);
    LCDCON2 = (VSPW<<0)|(VFPD<<6)|(LINEVAL<<14)|(VBPD<<24);
    LCDCON3 = (HFPD<<0)|(HOZVAL<<8)|(HBPD<<19);
    LCDCON4 = (HSPW<<0);
    LCDCON5 = (1<<11)|(1<<9)|(1<<8);
    TPAL = 0;	
}
void lcd_fram_init()
{
    /**allocate frame buffer**/	

    /****/
    LCDSADDR1 = (((unsigned int)frame>>22)<<21) | (((unsigned int)frame>>1)&0x1fffff);
    LCDSADDR2 = (((unsigned int)frame+240*320*2)>>1)&0x1fffff;
    LCDSADDR3 = (0<<11)|320;
}

void lcd_on()
{
    GPGCON |=(0x3<<8);
    LCDCON5 |=(1<<3);
    LCDCON1 |= (1<<0); 	
}



void lcd_init()
{
    lcd_port_init();
    
    lcd_timing_init();
    
    lcd_fram_init();
    
    lcd_on();  
}

void point(unsigned int x, unsigned int y, unsigned int color)
{
    unsigned int red,green,blue;
    red = (color>>19)&0x1f;
    green = (color>>10)&0x3f;
    blue = (color>>3)&0x1f;
    
    frame[y][x] = (unsigned short)((red<<11)|(green<<5)|blue);
    	
}


void Draw_picture(unsigned short x0,unsigned short y0, int wide, int high, const unsigned char* bmp)
{
    unsigned short x,y;
    unsigned short c;
    unsigned int p = 0;;
    for(y=y0;y<y0+high;y++)
        for(x=x0;x<y0+wide;x++)
        {
            c = bmp[p]|(bmp[p+1]<<8);
            if((x<320)&&(y<240))
                frame[y][x] = c;
                p +=2;
         }
}


void clearsrc(unsigned int color)
{
    TPAL = (1<<24)|(color&0xffffff);	
}


