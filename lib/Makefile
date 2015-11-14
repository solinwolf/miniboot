
OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))
OBJS = lib.o
$(OBJS) : $(OBJECTS)
	$(LD) -r $^ -o $@
%.o : %.c 
	$(GCC) -c -g $^ -o $@

.PHONY:clean
clean:
	rm -f *.o 
