


OBJECTS := start.o arm_main.o  dev/dev.o

miniboot.bin : miniboot.elf
	arm-linux-objcopy -O binary $^ $@
miniboot.elf : $(OBJECTS)
	arm-linux-ld -Tminiboot.lds -o $@ $^
	
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
	rm -f *.o *.elf *.bin *.bak *dump
	make -C dev clean
	make -C net clean
	make -C lib clean
