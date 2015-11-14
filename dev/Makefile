
objs := led.o 

all : $(objs)
	arm-linux-ld -r $^ -o dev.o


%.o : %.c 
	arm-linux-gcc -g -c $^ -o $@ 

%.o : %.S 
	arm-linux-gcc -g -c $^ -o $@ 

clean:
	rm -f *.o *.bak
