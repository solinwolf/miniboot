objs := string.o

all : $(objs)
	arm-linux-ld -r  $^ -o lib.o
%.o : %.S
	arm-linux-gcc -c -g $^ -o $@

%.o : %.c
	arm-linux-gcc -c -g $^ -o $@


clean:
	rm -f *.o *.bak
