


OBJECTS := start.o arm_main.o

miniboot.bin : miniboot.elf
	arm-linux-objcopy -O binary  miniboot.elf miniboot.bin
miniboot.elf : $(OBJECTS)
	arm-linux-ld -Tminiboot.lds -o miniboot.elf $^
	
%.o : %.S
	arm-linux-gcc -g -c $^ -o $@
	
%.o : %.c 
	arm-linux-gcc -g -c $^ -o $@
net/net.o : 
	make -C net all
dev/dev.o:
	make -C dev all
lib/lib.o:
	make -C lib all
.PHONY:clean
clean:
	rm -f *.o *.elf *.bin *.bak
	make -C dev clean
	make -C net clean
	make -C lib clean
