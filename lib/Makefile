
OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c)) $(patsubst %.S,%.o,$(wildcard *.S))
OBJS = lib.o
$(OBJS) : $(OBJECTS)
	$(LD) -r $^ -o $@
%.o : %.c 
	$(GCC) $(CFLAGS) -c $^ -o $@
%.o : %.S 
	$(GCC) $(CFLAGS) -c $^ -o $@

.PHONY:clean
clean:
	rm -f $(OBJECTS) lib.o 
