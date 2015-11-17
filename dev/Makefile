
OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c)) $(patsubst %.S,%.o,$(wildcard *.S))
OBJS = dev.o
$(OBJS) : $(OBJECTS)
	$(LD) -r $^ -o $@
%.o : %.c 
	$(GCC) $(CFLAGS) -c -g $^ -o $@
%.o : %.S 
	$(GCC) $(CFLAGS) -c -g $^ -o $@


.PHONY:clean
clean:
	rm -f $(OBJECTS)
