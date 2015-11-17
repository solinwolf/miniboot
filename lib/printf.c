


#include "vsprintf.h"

unsigned char outbuf[1024];
unsigned char inbuf[1024];
int printf(const char *fmt,...)
{
    int i;
    /**将可变参数转化为字符串**/
    va_list args;
   
    va_start(args,fmt);
     
    vsprintf((char*)outbuf, fmt,args);

    va_end();
    /**将转化后的字符串发送出去**/
    for(i=0;i<strlen((char*)outbuf);i++)
    {
        putc(outbuf[i]);
    }

}


int scanf(const char* fmt, ...)
{
	unsigned char c;
	int i = 0;
	va_list args;
	/**将字符串读回**/
	while (1)
	{
	 
	    c = getc();	
	    if ((c==0x0d) || (c==0x0a))
	    {
	    	inbuf[i] = '\n';
	    	break;
	    }
	    else
	    {
	        inbuf[i++] = c;	
	    }
	}
	/**将读回的字符串转化为可变参数**/
        va_start(args, fmt);
	vsscanf((char *)inbuf,fmt,args);
	va_end(args);
	
	return i;
}
