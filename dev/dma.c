
#define DISRC0     (*(volatile unsigned long *)0x4B000000)
#define DISRCC0    (*(volatile unsigned long *)0x4B000004)
#define DIDST0     (*(volatile unsigned long *)0x4B000008)
#define DIDSTC0    (*(volatile unsigned long *)0x4B00000c)
#define DCON0      (*(volatile unsigned long *)0x4B000010)
#define DMASKTRIG0  (*(volatile unsigned long *)0x4B000020)
#define UTXH0      ((volatile unsigned long *)0x50000020)

char *buff = "\nTesting DMA\n\r";

void dma_init()
{
    DISRC0 = (unsigned int)buff;
    DISRCC0 = (0<<1)|(0<<0);

    DIDST0 = UTXH0;
    DIDSTC0 = (1<<1)|(1<<0);

    DCON0 = (1<<24)|(1<<23)|(1<<22)|(strlen((char*)buff)<<0);
    
}

void dma_on()
{
    DMASKTRIG0 = (1<<1);
}




