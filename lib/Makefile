objs := string.o

all : $(objs)
	arm-linux-gcc -g -c $^ -o lib.o
%.o : %.S
	arm-linux-gcc -c -g $^ -o $@

%.o : %.c
	arm-linux-gcc -c -g $^ -o $@


clean:
	rm -f *.o *.bak
