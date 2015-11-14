
OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))
OBJS = dev.o
$(OBJS) : $(OBJECTS)
	$(LD) -r $^ -o $@
%.o : %.c 
	$(GCC) -c -g $^ -o $@

.PHONY:clean
clean:
	rm -f $(OBJECTS)
