TOPDIR  = $(shell pwd)
export TOPDIR

BOARD = mini2440
ARCH = arm
CPU = s3c2440
export BOARD ARCH CPU

ifeq ($(ARCH),arm)
CROSS_COMPILE = arm-linux-
endif

GCC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
export CROSS_COMPILE GCC LD OBJCOPY
 
CFLAGS = -nostdinc -I$(TOPDIR)/include -fno-builtin
export CFLAGS

ELF = miniboot.elf
BIN  = miniboot.bin
OBJECTS = $(patsubst %.c,%.o, $(wildcard *.c)) $(patsubst %.S,%.o,$(wildcard *.S))\
 $(TOPDIR)/dev/dev.o $(TOPDIR)/net/net.o $(TOPDIR)/lib/lib.o

$(BIN) : $(ELF)
	$(OBJCOPY) -O binary  $^ $@
$(ELF) : $(OBJECTS)
	$(LD) -Tminiboot.lds -o $@ $^
%.o : %.c
	$(GCC) $(CFLAGS) -c $^ -o $@
%.o : %.S
	$(GCC) $(CFLAGS) -c $^ -o $@
$(TOPDIR)/dev/dev.o :$(TOPDIR)/dev/*.c
	@cd $(TOPDIR)/dev &&make
$(TOPDIR)/net/net.o :$(TOPDIR)/net/*.c
	@cd $(TOPDIR)/net &&make
$(TOPDIR)/lib/lib.o :$(TOPDIR)/lib/*.c
	@cd $(TOPDIR)/lib &&make
.PHONY :clean
clean:
	@cd $(TOPDIR)/dev && make clean
	@cd $(TOPDIR)/net && make clean
	@cd $(TOPDIR)/lib && make clean
	rm  $(OBJECTS) $(BIN) $(ELF)
.PHONY:env
env:
	@echo top_directory=$(TOPDIR)
	@echo compile_chain:
	@echo gcc=$(GCC)
	@echo objcopy=$(OBJCOPY)
	@echo ld=$(LD)
	





