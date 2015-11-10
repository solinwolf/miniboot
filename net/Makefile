objs := arp.o tftp.o

all : $(objs)
	arm-linux-gcc -g -c $^ -o net.o	

%.o : %.c
	arm-linux-gcc -g -c $^ -o $@

%.o : %.S
	arm-linux-gcc -g -c $^ -o $@

clean:
	rm -f *.o *.bak
