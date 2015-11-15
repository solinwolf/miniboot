#define NFCONF (*(volatile unsigned long*)0x4E000000)
#define NFCONT (*(volatile unsigned long*)0x4E000004)
#define NFCMMD (*(volatile unsigned char*)0x4E000008)
#define NFADDR (*(volatile unsigned char*)0x4E00000C)
#define NFDATA (*(volatile unsigned char*)0x4E000010)
#define NFSTAT (*(volatile unsigned char*)0x4E000020)


#define TACLS 1
#define TWRPH0 2
#define TWRPH1 1

/**片选**/
void select_chip()
{
    NFCONT &=~(1<<1);       
}
/***释放片选**/
void diselect_chip()
{
    NFCONT |=(1<<1);
}
/**清除RnB信号，为下次操作nand flash 做准备**/
void clear_RnB()
{
    NFSTAT |=(1<<2);
}
/**发送命令**/
void send_cmmd(unsigned cmmd)
{
    NFCMMD = cmmd;
}

/**发送地址**/
void send_addr(unsigned addr)
{
    NFADDR = addr;
}

/**等待nand flash 释放RnB信号**/
void wait_RnB()
{
    while(!(NFSTAT&(1<<2)));
}

/***复位控制器****/
void nand_reset()
{
    /**片选**/
    select_chip();
   
    /***清除RnB 信号**/
    clear_RnB();

    /***发送命令 0xff ***/
    send_cmmd(0xff);

    /**等待RnB 信号**/
    wait_RnB();

    /**释放片选**/
    diselect_chip();      
}

/***初始化nand 控制器，并打开控制器**/
void nand_init()
{   /**初始化配置寄存器，设置几个信号等待时间**/
    NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
    /**设置控制寄存器，初始化RnB信号，并开启NAND 控制器**/
    NFCONT = (1<<0)|(1<<1);
    /**将nand 控制器复位**/
    nand_reset();  
}

/****读取一页的数据****/ 
void nand_PageRead(unsigned long addr, unsigned char *buff)
{
    int i = 0;
    /**片选**/
    select_chip();
    
    /**清除RnB 信号**/
    clear_RnB();
       
    /**发送命令 0x00 **/
    send_cmmd(0x00);

    /**发送列地址，由于是按照Page 读，所以列地址填0 即可**/
    send_addr(0x00);
    send_addr(0x00);

    /**发送行地址，即Page号**/ 
    send_addr(addr&0xff);
    send_addr((addr>>8)&0xff);
    send_addr((addr>>16)&0xff);

    /**发送命令0X30**/
    send_cmmd(0x30);

    /**等待RnB信号**/
    wait_RnB();
    
    /**读取数据**/
    for(i=0;i<2048;i++)
    {
        buff[i] = NFDATA;
    }   
  
    /**释放片选**/
    diselect_chip();

}









