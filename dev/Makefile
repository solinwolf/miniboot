
objs := dm9000.o dma.o interrupt.o lcd.o led.o nand.o ts.o uart.o

all : $(objs)
	arm-linux-gcc -c -g $^ -o dev.o


%.o : %.c 
	arm-linux-gcc -g -c $^ -o $@ 

%.o : %.S 
	arm-linux-gcc -g -c $^ -o $@ 

clean:
	rm -f *.o *.bak
